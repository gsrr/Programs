/* **************************************************************************
 * Copyright 2010 VMware, Inc.  All rights reserved.
 * **************************************************************************/

/*
 * ExampleNas.c:
 * This plugin implements an example loadable DiskLib plugin that uses SUN PRC
 * protocol to implement NAS plugin API primitives over NFS2.
 */

#include "pluginInt.h"

static VixDiskLibNasPluginStartSession ExampleNas_StartSession;
static VixDiskLibNasPluginEndSession ExampleNas_EndSession;
static VixDiskLibNasPluginExecutePrimitive ExampleNas_ExecPrimitive;
static VixDiskLibNasPluginSupportStatus ExampleNas_SupportStatus;

static VixError ExampleNasCloneFile(exNasPluginSession *, 
                                    exNasPluginSession *, 
                                    VixDiskLibNasPluginCloneFileParams *);
static VixError ExampleNasGetXStats(exNasPluginSession*, 
                                    VixDiskLibNasPluginStatXParams*);
static VixError ExampleNasReserveSpace(exNasPluginSession *,
                                       VixDiskLibNasPluginResvSpaceParams *);
static void ExampleNasFreeSession(exNasPluginSession *session);
static VixError ExampleNasLookupFH(exNasPluginSession *session, 
                                   char *pathName,
                                   Bool create,
                                   VixDiskLibNasPluginCloneFileFlags createFlags,
                                   nfs_fh *fh,
                                   fattr *attributes);
static void ExampleNasInsertSession(exNasPluginSession *session);
static void ExampleNasRemoveSession(exNasPluginSession *session);
static VixError ExampleNasMakeVixError(int rpcError,
                                       nfsstat nfsStatus,
                                       int mountError);


// default timeout of 10 sec for the RPC client
static struct timeval exDefaultTimeout = {10, 0};

/* Buffer with zeroes */
char gZeroBuf[NFS_MAXDATA];

// global session list
pthread_mutex_t gSessionListLock = PTHREAD_MUTEX_INITIALIZER;
exNasPluginSession *gSessionHead = NULL;

/* The interface for the ExampleNas plugin as exported by this library. */
VixDiskLibNasPlugin ExampleNasPlugin = {
   {
      VIXDISKLIB_NASPLUGIN_MAJOR_VERSION,
      VIXDISKLIB_NASPLUGIN_MINOR_VERSION,
      VIXDISKLIB_PLUGIN_TYPE_NAS,
      "ExampleNasPlugin",
      ExampleNas_PluginInit,
      ExampleNas_PluginDone
   },
   ExampleNas_StartSession,    
   ExampleNas_EndSession,        
   ExampleNas_ExecPrimitive,
   ExampleNas_SupportStatus
};

/*
 * Functions exported by the function table describing the NAS plugin.
 */


/*
 *-----------------------------------------------------------------------------
 * ExampleNas_StartSession --                                            */ /**
 * 
 * \ingroup EXAMPLE_NAS_PLUGIN
 * \brief Initialize new NAS offload session based on the passed in parameters
 *
 * \param[in] nasConfigData NAS datastore parameters such as remote IP address
 * \param[in] sessionParams Optional session operational parameters
 * \param[out] sessionID ID of the newly created session
 * 
 * \returns VIX error code.
 *
 *-----------------------------------------------------------------------------
 */

VixError
ExampleNas_StartSession(const VixDiskLibNasPluginDataStoreParams *nasConfigData,
                        const VixDiskLibNasPluginSessionParams *sessionParams,
                        VixDiskLibNasPluginSessionID *sessionID)
{
   exNasPluginSession *session;
   int ret;
   CLIENT *mount_clnt;
   fhstatus mfhstatus;
   dirpath remoteMP = nasConfigData->remoteMountPoint;

   Log(LGPFX" session request for %s %s %s %s %d \n", 
       nasConfigData->remoteIP, nasConfigData->remoteMountPoint,
       nasConfigData->localMountPoint, nasConfigData->fsType, 
       nasConfigData->fsVersion);

   *sessionID = VIXDISKLIB_NASPLUGIN_INVALID_SESSION_ID;

   /*
    * We only support files on NFS
    */
   if ((strcmp(nasConfigData->fsType, VIXDISKLIB_NASPLUGIN_FSTYPE_NFS) != 0) ||
       nasConfigData->remoteIP == NULL ||
       nasConfigData->remoteMountPoint == NULL) {
      Log(LGPFX" reject non-NFS params \n");
      return VIX_E_NOT_SUPPORTED;
   }

   /* 
    * Create new session and store session parameters in it
    */
   session = malloc(sizeof(*session));

   if (session == NULL) {
      return VIX_E_OUT_OF_MEMORY;
   }

   session->magic = EXAMPLE_NAS_PLUGIN_SESS_MAGIC;
   session->timeout = exDefaultTimeout;
   if (sessionParams) {
      session->timeout.tv_sec = sessionParams->timeoutMS / MS_PER_SEC;
      session->timeout.tv_usec = (sessionParams->timeoutMS - 
                                  session->timeout.tv_sec * MS_PER_SEC) * MS_PER_SEC;
   }

   session->remoteIP = strdup(nasConfigData->remoteIP);
   session->remoteMountPoint = strdup(nasConfigData->remoteMountPoint);
   session->localMountPoint = strdup(nasConfigData->localMountPoint);
   session->localMPLen = strlen(session->localMountPoint);
   session->next = NULL;
   session->prev = NULL;

   /*
    * create a new RPC NFS session
    */
   session->clnt = clnt_create(session->remoteIP, NFS_PROGRAM, NFS_VERSION, "udp");

   if (!session->clnt) {
      Log(LGPFX" could not create RPC client for the remote host %s %s\n", 
           session->remoteIP, clnt_spcreateerror("error:"));
      ExampleNasFreeSession(session);
      return VIX_E_FAIL;
   }

   /*
    * Set authentication type to Unix
    */
   auth_destroy(session->clnt->cl_auth);
   session->clnt->cl_auth = authunix_create_default();
   if(session->clnt->cl_auth == NULL) {
      Log(LGPFX" Coul not set Auth flavor to Unix \n");
      ExampleNasFreeSession(session);
      return VIX_E_FAIL;
   } 

   /*
    * Ping NFS server with a NULL request just to make sure it exists
    */
   ret = clnt_call(session->clnt, NFSPROC_NULL,
                   (xdrproc_t) xdr_void, NULL, (xdrproc_t) xdr_void, NULL,
                   session->timeout);

   if (ret != RPC_SUCCESS) {
      Log(LGPFX" could not connect to the remote host %s; \n"
          "   prog %d version %d proc %d; status %d %s\n", 
          session->remoteIP, 
          NFS_PROGRAM, NFS_VERSION, NFSPROC_NULL,
          ret, clnt_sperror(session->clnt, " "));

      ExampleNasFreeSession(session);

      return VIX_E_HOST_CONNECTION_LOST;
   }

   /*
    * Get the file handle of the mount point via mount protocol
    */
   mount_clnt = clnt_create(session->remoteIP, MOUNTPROG, MOUNTVERS, "udp");

   if (!mount_clnt) {
      Log(LGPFX" could not create RPC mount client for the remote host %s %s\n", 
           session->remoteIP, clnt_spcreateerror("error:"));
      ExampleNasFreeSession(session);
      return VIX_E_FAIL;
   }

   /*
    * Set authentication type to Unix
    */
   auth_destroy(mount_clnt->cl_auth);
   mount_clnt->cl_auth = authunix_create_default();
   if(mount_clnt->cl_auth == NULL) {
      Log(LGPFX" Coul not set Auth flavor to Unix \n");
      ExampleNasFreeSession(session);
      clnt_destroy(mount_clnt);
      return VIX_E_FAIL;
   } 

   memset(&mfhstatus, 0, sizeof(mfhstatus));
   ret = mountproc_mnt_1(&remoteMP, &mfhstatus, mount_clnt);

   if (ret == RPC_SUCCESS && mfhstatus.fhs_status == 0) {
      memcpy(session->rootFH, mfhstatus.fhstatus_u.fhs_fhandle, 
             sizeof(session->rootFH));
      ret = VIX_OK;
       Log(LGPFX" mounted %s on host %s \n", 
          session->remoteMountPoint, session->remoteIP);
   } else {
      Log(LGPFX" could not mount %s on host %s; status: (RPC=%d NFS=%d).\n", 
          session->remoteMountPoint, session->remoteIP, ret, 
          mfhstatus.fhs_status);

      ExampleNasFreeSession(session);
      session = NULL;
      ret = ExampleNasMakeVixError(ret, NFS_OK, mfhstatus.fhs_status);
   }

   /*
    * Don't need the mount client anymore
    */
   clnt_freeres(mount_clnt, (xdrproc_t) xdr_fhstatus, (caddr_t) &mfhstatus); 
   clnt_destroy(mount_clnt);

   /*
    * Use session structure pointer as our sessionID 
    */
   *sessionID = MAKE_SESSION_ID(session);

   if (session) {
      ExampleNasInsertSession(session);
   }

   return ret;
}


/*
 *-----------------------------------------------------------------------------
 * ExampleNas_EndSession --                                              */ /**
 * 
 * \ingroup EXAMPLE_NAS_PLUGIN
 * \brief Destroy the NAS offload session 
 * \param[in] sessionID The ID of the session to be destoryed
 * 
 * \returns VIX error code.
 *
 *-----------------------------------------------------------------------------
 */

static VixError
ExampleNas_EndSession(VixDiskLibNasPluginSessionID sessionID)
{
   exNasPluginSession *session = GET_SESSION_FROM_ID(sessionID);

   if (sessionID == VIXDISKLIB_NASPLUGIN_INVALID_SESSION_ID) {
      return VIX_E_INVALID_ARG;
   }

   ExampleNasFreeSession(session);

   return VIX_OK;
}


/*
 *-----------------------------------------------------------------------------
 * ExampleNas_ExecPrimitive --                                           */ /**
 * 
 * \ingroup EXAMPLE_NAS_PLUGIN
 * \brief Execute the NAS offload primitive  
 * \param[in] sessionID The ID of the NAS session
 * \param[in/out] execParams Parameters for the offload primitive 
 *                and the result
 * 
 * \returns void
 *
 *-----------------------------------------------------------------------------
 */

list *mk_list(char* remoteIP, char* mountPoint, char* filePath, int size)
{
	list *lst;

	lst = (list*)malloc(sizeof(list));
	if (lst == NULL)
		return NULL;
	lst->IP = remoteIP;
	lst->mountPoint = mountPoint;
	lst->filePath = filePath;
	lst->size = size;
	return lst;
}

static int call_print_list(char* remoteIP, char* mountPoint, char* filePath, int size)
{
	list *l;
	int *result;
	CLIENT* cl = clnt_create(remoteIP, PRINTER, PRINTER_V1, "udp");
	l = mk_list(remoteIP, mountPoint, filePath, size);
	if (cl == NULL) {
		printf("error: could not connect to server.\n");
		return 1;
	}
	result = print_list_1(l, cl);
	if (result == NULL) {
		printf("error: RPC failed!\n");
		return 1;
	}
	return 0;

}
static void
ExampleNas_ExecPrimitive(VixDiskLibNasPluginSessionID sessionID,
                         const VixDiskLibNasPluginCommonParams *execParams)
{
   Log(LGPFX"start to execPrimitive\n"); 
   system("touch /vmfs/volumes/datastore1/rpc_test");
   exNasPluginSession *session = GET_SESSION_FROM_ID(sessionID);

   ASSERT(session->magic == EXAMPLE_NAS_PLUGIN_SESS_MAGIC);

   switch(execParams->primitiveID) {
   case VIXDISKLIB_NASPLUGIN_PRIM_CLONEFILE:
   {
      VixDiskLibNasPluginCloneFileParams *cloneParams = 
         (VixDiskLibNasPluginCloneFileParams *) execParams;
      exNasPluginSession *srcSession = NULL;
      VixDiskLibNasPluginSessionID srcSessionID = 
         VIXDISKLIB_NASPLUGIN_INVALID_SESSION_ID;
      VixDiskLibNasPluginSessionParams sessionParams;
      VixError status;

      if (cloneParams->cloneFlags & 
          VIXDISKLIB_NASPLUGIN_CLONEFILE_FLAG_SRCDATASTORE_VALID) {
         // Start a session for the source file

         // Use the same timeout as the dest session
         sessionParams.timeoutMS = session->timeout.tv_usec /MS_PER_SEC +
            session->timeout.tv_sec * MS_PER_SEC;

         status = ExampleNas_StartSession(cloneParams->srcDataStoreInfo,
                                          &sessionParams,
                                          &srcSessionID);
         if (status == VIX_OK) {
            srcSession = GET_SESSION_FROM_ID(srcSessionID);
         } else {
            execParams->result->status = status;
            return;
         }
      } else {
         srcSession = session;
      }

      execParams->result->status = ExampleNasCloneFile(srcSession, session,
                                                       cloneParams);

      if (srcSessionID != VIXDISKLIB_NASPLUGIN_INVALID_SESSION_ID) {
         ExampleNas_EndSession(srcSessionID);
      }
      
      break;
   }
   case VIXDISKLIB_NASPLUGIN_PRIM_STATX:
   {
      VixDiskLibNasPluginStatXParams *xstatsParams =
         (VixDiskLibNasPluginStatXParams*) execParams;

      execParams->result->status = ExampleNasGetXStats(session, xstatsParams);
      
      break;

   }
   case VIXDISKLIB_NASPLUGIN_PRIM_RESVSPACE:
   {
      VixDiskLibNasPluginResvSpaceParams *resSpaceParams = 
         (VixDiskLibNasPluginResvSpaceParams *) execParams;

      execParams->result->status = ExampleNasReserveSpace(session,
                                                          resSpaceParams);

      break;
   }
   default:
      execParams->result->status =  VIX_E_NOT_SUPPORTED;
   }

   return;
}


/*
 * Internal functions
 */


/*
 *-----------------------------------------------------------------------------
 * ExampleNasInsertSession --                                            */ /**
 * 
 * \ingroup EXAMPLE_NAS_PLUGIN
 * \brief Insert session into the global session list
 * \param[in] session session to insert.
 * 
 * \returns void
 *
 *-----------------------------------------------------------------------------
 */

static void 
ExampleNasInsertSession(exNasPluginSession *session)
{
   pthread_mutex_lock(&gSessionListLock);

   // Insert at the head
   session->next = gSessionHead;
   session->prev = NULL;
   if (gSessionHead) {
      gSessionHead->prev = session;
   }
   gSessionHead = session;

   pthread_mutex_unlock(&gSessionListLock);
}


/*
 *-----------------------------------------------------------------------------
 * ExampleNasRemoveSession --                                            */ /**
 * 
 * \ingroup EXAMPLE_NAS_PLUGIN
 * \brief Remove session from the global session list
 * \param[in] session session to remove; may be NULL.
 * 
 * \returns void
 *
 *-----------------------------------------------------------------------------
 */

static void 
ExampleNasRemoveSession(exNasPluginSession *session)
{
   // Check if session exist
   if (session == NULL) {
      return;
   }

   pthread_mutex_lock(&gSessionListLock);

   // session could be unlinked
   if (session->prev) {
      session->prev->next = session->next;
   }

   if (session->next) {
      session->next->prev = session->prev;
   }

   if (session == gSessionHead) {
      gSessionHead = session->next;
   }

   session->next = NULL;
   session->prev = NULL;

   pthread_mutex_unlock(&gSessionListLock);
}


/*
 *-----------------------------------------------------------------------------
 * ExampleNasFreeSession --                                              */ /**
 * 
 * \ingroup EXAMPLE_NAS_PLUGIN
 * \brief Cleanup and free the plugin offload session
 * \param[in] sessionID The ID of the NAS session
 * 
 * \returns void
 *
 *-----------------------------------------------------------------------------
 */

static void 
ExampleNasFreeSession(exNasPluginSession *session)
{
   ASSERT(session->magic == EXAMPLE_NAS_PLUGIN_SESS_MAGIC);

   ExampleNasRemoveSession(session);

   if (session->clnt) {
      clnt_destroy(session->clnt);
   }
   
   free(session->remoteIP);
   free(session->remoteMountPoint);
   free(session->localMountPoint);

   free(session);

   return;
}


/*
 *-----------------------------------------------------------------------------
 * ExampleNasMakeVixError --                                             */ /**
 * 
 * \ingroup EXAMPLE_NAS_PLUGIN
 * \brief Convert combination of the PRC and NFS/Mount errors to a vix error
 *
 * 
 * \param[in] rpcError  RPC error code
 * \param[in] nfsStatus NFS status code 
 * \param[in] mountError Mount protocol error code
 * 
 * \returns VixError
 *
 *-----------------------------------------------------------------------------
 */

static VixError 
ExampleNasMakeVixError(int rpcError, nfsstat nfsStatus, int mountError)
{
   switch (rpcError) {
   case RPC_SUCCESS:
      if (mountError != MOUNT_OK) {
         return VIX_E_OBJECT_NOT_FOUND;
      }

      switch (nfsStatus) {
      case 	NFS_OK:
         return VIX_OK;
      case NFSERR_PERM :
      case NFSERR_ACCES:
         return VIX_E_FILE_ACCESS_ERROR;
      case NFSERR_NOENT:
      case NFSERR_NODEV:
         return VIX_E_FILE_NOT_FOUND;     
      case NFSERR_EXIST:
         return VIX_E_FILE_ALREADY_EXISTS;         
      case NFSERR_ISDIR:
         return VIX_E_INCORRECT_FILE_TYPE;
      case NFSERR_FBIG:
         return VIX_E_FILE_TOO_BIG;
      case NFSERR_NOSPC:
         return VIX_E_DISK_FULL;
      case NFSERR_ROFS:
         return VIX_E_FILE_READ_ONLY;
      case NFSERR_NAMETOOLONG:
         return VIX_E_FILE_NAME_INVALID; 
      default:
         return VIX_E_FILE_ERROR;
      }
      break;  
   case RPC_AUTHERROR:		/* authentication error */
      return VIX_E_AUTHENTICATION_FAIL;
   case RPC_VERSMISMATCH:		/* rpc versions not compatible */
   case RPC_PROGUNAVAIL:		/* program not available */
   case RPC_PROGVERSMISMATCH:		/* program version mismatched */
   case RPC_PROCUNAVAIL:		/* procedure unavailable */
   case RPC_CANTDECODEARGS:		/* decode arguments error */
   case RPC_SYSTEMERROR:		/* generic "other problem" */
   case RPC_NOBROADCAST:		/* Broadcasting not supported */
      return VIX_E_NOT_SUPPORTED_ON_REMOTE_OBJECT;
   case RPC_UNKNOWNHOST:		/* unknown host name */ 
   case RPC_UNKNOWNADDR:		/* Remote address unknown */
       return VIX_E_HOST_NOT_CONNECTED;
   case RPC_UNKNOWNPROTO:		/* unknown protocol */
      return VIX_E_NOT_SUPPORTED;
   default:
      return VIX_E_FAIL;
   }
}


/*
 *-----------------------------------------------------------------------------
 * ExampleNasLookupFH --                                                 */ /**
 * 
 * \ingroup EXAMPLE_NAS_PLUGIN
 * \brief Lookup the NFS file handle correspoding to the pathName
 *
 * Lookup the NFS file handle correspoding to the pathName. If the 'create'
 * flag is set, then the file may be created if it does not exist. If the
 * 'create' flag is not set, then the file must already exist. In either case,
 * the directory has to already exist.
 *
 * If successful, return file handle and file attributes
 * 
 * \param[in] session Nas Plugin NAS session
 * \param[in] pathName Path name relative to the mount point
 * \param[in] create Create flag. If set, the file may be created.
 * \param[in] guarded Guarded flag. Only valid if 'create' flag is set. See
 *                    VIXDISKLIB_NASPLUGIN_CLONEFILE_FLAG_GUARDED.
 * \param[out] fs Resulting NFS file handle
 * \param[out] attributes Resulting NFS file attributes
 * 
 * \returns VixError
 *
 *-----------------------------------------------------------------------------
 */

static VixError
ExampleNasLookupFH(exNasPluginSession *session, 
                   char *pathName,
                   Bool create,
                   VixDiskLibNasPluginCloneFileFlags createFlags,
                   nfs_fh *fh,
                   fattr *attributes)
{
   diropres dirres;
   diropargs args;
   char *fileName;
   char *tmpPathName;
   nfs_fh parentFH;
   fattr attr;
   VixError status;
   nfsstat nfsStatus;
   int ret;
   char *itr = NULL;
   Bool guarded = (Bool) createFlags & VIXDISKLIB_NASPLUGIN_CLONEFILE_FLAG_GUARDED;
   Bool dryrun = (Bool) createFlags & VIXDISKLIB_NASPLUGIN_CLONEFILE_FLAG_DRYRUN;

   memcpy(parentFH.data, session->rootFH, sizeof(session->rootFH));
   tmpPathName = strdup(pathName);

   for (fileName = strtok_r(tmpPathName, "/", &itr); 
        fileName;
        fileName = strtok_r(NULL, "/", &itr)) {

      memset(&dirres, 0, sizeof(dirres));

      args.name = fileName;
      args.dir = parentFH; // struct copy
      
      ret = nfsproc_lookup_2(&args, &dirres, session->clnt);
      nfsStatus = dirres.status;
      status = ExampleNasMakeVixError(ret, nfsStatus, MOUNT_OK);

      if (status == VIX_OK) {
         parentFH = dirres.diropres_u.diropres.file; // struct copy
         attr = dirres.diropres_u.diropres.attributes; // struct copy
      }

      clnt_freeres(session->clnt, (xdrproc_t) xdr_diropres, (caddr_t) &dirres); 

      if (status != VIX_OK) {
         break;
      } 
   }

   if (create) {
      // The file may be created (if it does not exist yet)

      if (status == VIX_OK && guarded) {
         // The file already exists and we should bail out if it does.

         Log(LGPFX" The file '%s' already exists but the GUARDED flag is set.\n",
             pathName);
         status = VIX_E_FILE_ALREADY_EXISTS;
      } else if (status == VIX_E_FILE_NOT_FOUND && 
                 strtok_r(NULL, "/", &itr) == NULL) {
         // The file name does not exit, but directory does
        
         if (dryrun) {
            // For dry run we are done
            status = VIX_OK;
            goto lookup_done;
         } 

         createargs cargs;

         cargs.where.dir = parentFH;
         cargs.where.name = fileName;
         if (attributes) {
            // use what whas passed in
            cargs.attributes.mode = attributes->mode;
            cargs.attributes.gid = attributes->gid;
            cargs.attributes.uid = attributes->uid;
         } else {
            // use something reasonalble
            cargs.attributes.mode = 0666;
            cargs.attributes.gid = attr.gid;
            cargs.attributes.uid = attr.uid;
         }
         cargs.attributes.size = 0;
         cargs.attributes.atime.seconds = -1;
         cargs.attributes.atime.useconds = -1;
         cargs.attributes.mtime.seconds = -1;
         cargs.attributes.mtime.useconds = -1;

         memset(&dirres, 0, sizeof(dirres)); 
         ret = nfsproc_create_2(&cargs, &dirres, session->clnt);
         nfsStatus = dirres.status;
         status = ExampleNasMakeVixError(ret, nfsStatus, MOUNT_OK);

         clnt_freeres(session->clnt, (xdrproc_t) xdr_diropres, 
                      (caddr_t) &dirres); 

         if (status == VIX_OK) {
            // Now do a lookup again
            memset(&dirres, 0, sizeof(dirres)); 
            ret = nfsproc_lookup_2(&args, &dirres, session->clnt);
            nfsStatus = dirres.status;
            status = ExampleNasMakeVixError(ret, nfsStatus, MOUNT_OK);

            if (status == VIX_OK) {
               // struct copy
               parentFH = dirres.diropres_u.diropres.file;
               // struct copy
               attr = dirres.diropres_u.diropres.attributes;
            }

            clnt_freeres(session->clnt, (xdrproc_t) xdr_diropres, 
                         (caddr_t) &dirres); 
         } else {
            Log(LGPFX" Failed to create for %s. Error (RPC=%d NFS=%d). \n", 
                fileName, ret, nfsStatus);
         }
      }
   }

lookup_done:
   if (status == VIX_OK) {
      if (fh) {
         *fh = parentFH; // struct copy
      }

      if (attributes) {
         *attributes = attr; // struct copy
      }
   } else {
       Log(LGPFX" Failed to lookup FD for %s (create=%s, guarded=%s). "
           "Error %d (RPC=%d NFS=%d). \n", pathName,
           create ? "TRUE" : "FALSE", guarded ? "TRUE" : "FALSE",
           (uint32) status, ret, nfsStatus);
   }

   free(tmpPathName);
   return status;
}


/*
 *-----------------------------------------------------------------------------
 * ExampleNasCloneFile --                                                */ /**
 * 
 * \ingroup EXAMPLE_NAS_PLUGIN
 * \brief Execute Clone File primitive
 * 
 * \param[in] session Nfs Plugin NAS session
 * \param[in] cloneParams Clone File parameters
 * 
 * \returns VixError
 *
 *-----------------------------------------------------------------------------
 */

VixError
ExampleNasCloneFile(exNasPluginSession *srcSession,
                    exNasPluginSession *dstSession, 
                    VixDiskLibNasPluginCloneFileParams *cloneParams)
{
   char *srcPath, *dstPath;
   nfs_fh srcFH, dstFH;
   fattr attributes;
   uint64 len, offset, size;
   uint64 lastReportedOffset;
   VixError status;

   Log(LGPFX" request to copy %s to %s flags %x \n", 
       cloneParams->srcFileName, cloneParams->dstFileName,
       cloneParams->cloneFlags);

   if (strncmp(cloneParams->srcFileName, srcSession->localMountPoint, 
               srcSession->localMPLen) != 0 ||
       strncmp(cloneParams->dstFileName, dstSession->localMountPoint, 
               dstSession->localMPLen) != 0 ) {
      return VIX_E_INVALID_ARG;
   }

   /*
    * Get path relative to the local mount point
    */
   srcPath = &cloneParams->srcFileName[srcSession->localMPLen + 1];
   dstPath = &cloneParams->dstFileName[dstSession->localMPLen + 1];

   /*
    * lookup file handles
    */
   status = ExampleNasLookupFH(srcSession, srcPath, FALSE, 0, &srcFH, &attributes);
   if (status != VIX_OK) {
      return status;
   }
   size = attributes.size; 

   status = ExampleNasLookupFH(dstSession, dstPath, TRUE, 
                               cloneParams->cloneFlags,
                               &dstFH, &attributes);

   if (status != VIX_OK ||
       (cloneParams->cloneFlags & VIXDISKLIB_NASPLUGIN_CLONEFILE_FLAG_DRYRUN)) {
      return status;
   }

   /*
    * A hack to test VIX_E_SNAPSHOT_HIERARCHY_TOODEEP handling
    * for lazyClones
    */
   if (cloneParams->cloneFlags & VIXDISKLIB_NASPLUGIN_CLONEFILE_FLAG_LAZY &&
       strstr(dstPath, "errorHierarchyTooDeep") != NULL) {
      status = VIX_E_SNAPSHOT_HIERARCHY_TOODEEP;
      Log(LGPFX" DEBUG: Failing with error VIX_E_SNAPSHOT_HIERARCHY_TOODEEP"
               " (0x%x).\n", status);
      return status;
   }

   if (cloneParams->cloneFlags & VIXDISKLIB_NASPLUGIN_CLONEFILE_FLAG_LAZY &&
       strstr(dstPath, "errorTooManySnaps") != NULL) {
      status = VIX_E_SNAPSHOT_MAXSNAPSHOTS;
      Log(LGPFX" DEBUG: Failing with error VIX_E_SNAPSHOT_MAXSNAPSHOTS"
               " (0x%x).\n", status);
      return status;
   }

   if (strstr(dstPath, "errorTooManyConcurent") != NULL) {
      status = VIX_E_OBJECT_IS_BUSY;
      Log(LGPFX" DEBUG: Failing with error VIX_E_OBJECT_IS_BUSY"
               " (0x%x).\n", status);
      return status;
   }

   for (offset = 0, lastReportedOffset = 0; offset < size; offset += len) {
      readargs rdargs;
      writeargs wrtargs;
      readres rdres;
      attrstat wrtres;
      int ret;
      nfsstat nfsStatus;
      
      /*
       * report progress
       */
      if (cloneParams->common.progressRecord->updateBytes > 0 &&
          offset - lastReportedOffset >= 
          cloneParams->common.progressRecord->updateBytes) {
         Bool opContinue;

         cloneParams->common.progressRecord->progressBytes = 
            offset - lastReportedOffset;

         opContinue = cloneParams->common.progressRecord->callback(
            cloneParams->common.progressRecord);
         // reset lastReportedOffset
         lastReportedOffset = offset;

         if (opContinue == FALSE) {
            Log(LGPFX" Operation cancelled by caller offset=%lld size=%lld. \n",
                offset, size);
            return VIX_E_CANCELLED;
         }
      }

      /*
       * calculate the length of the next transfer
       */
      len = MIN(NFS_MAXDATA, size - offset);

      rdargs.file = srcFH;
      rdargs.offset = offset;
      rdargs.count = len;
      rdargs.totalcount = 0; // ignored

      memset(&rdres, 0, sizeof(rdres));
      ret = nfsproc_read_2(&rdargs, &rdres, srcSession->clnt);
      nfsStatus = rdres.status;
      status = ExampleNasMakeVixError(ret, nfsStatus, MOUNT_OK);

      if (status != VIX_OK) {
         Log(LGPFX" Failed read from %s, offset %lld. Error (RPC=%d NFS=%d). \n", 
             cloneParams->srcFileName, offset, ret, nfsStatus);

         clnt_freeres(srcSession->clnt, (xdrproc_t) xdr_readres, (caddr_t) &rdres); 

         return status;
      }

      if (len != rdres.readres_u.reply.data.data_len) {
         Log(LGPFX" Failed read from %s, offset %lld. "
                  "Got %d bytes instead of %d \n", 
             cloneParams->srcFileName, offset, 
             rdres.readres_u.reply.data.data_len, len);

         clnt_freeres(srcSession->clnt, (xdrproc_t) xdr_readres, (caddr_t) &rdres); 

         return VIX_E_FILE_ERROR;
      }

      /*
       * if we are asked to skip zeroes, check if the read data is all zeroes,
       * and skip write in this case.
       */
      if (cloneParams->cloneFlags &
          VIXDISKLIB_NASPLUGIN_CLONEFILE_FLAG_SKIPZEROES) {
         if (memcmp(rdres.readres_u.reply.data.data_val, gZeroBuf, len) == 0) {
             clnt_freeres(srcSession->clnt, (xdrproc_t) xdr_readres,
                          (caddr_t) &rdres);
             continue;
         }
      }

      wrtargs.file = dstFH;
      wrtargs.offset = offset;
      wrtargs.totalcount = 0; // ignored
      wrtargs.beginoffset = 0; // ignored
      wrtargs.data.data_len = rdres.readres_u.reply.data.data_len;
      wrtargs.data.data_val = rdres.readres_u.reply.data.data_val;

      memset(&wrtres, 0, sizeof(wrtres));
      ret =  nfsproc_write_2(&wrtargs, &wrtres, dstSession->clnt);
      nfsStatus = wrtres.status;
      status = ExampleNasMakeVixError(ret, nfsStatus, MOUNT_OK);

      // we don't need read or write data anymore
      clnt_freeres(srcSession->clnt, (xdrproc_t) xdr_readres, (caddr_t) &rdres); 
      clnt_freeres(dstSession->clnt, (xdrproc_t) xdr_attrstat, (caddr_t) &wrtres); 

      if (status != VIX_OK) {
         Log(LGPFX" Failed write to %s, offset %lld. Error (RPC=%d NFS=%d). \n", 
              cloneParams->dstFileName, offset, ret, nfsStatus);
         return status;
      }
   }

   return VIX_OK;
}


/*
 *-----------------------------------------------------------------------------
 * ExampleNasGetXStats --                                                */ /**
 * 
 * \ingroup EXAMPLE_NAS_PLUGIN
 * \brief Execute Extended Stats primitive
 * 
 * \param[in] session Nfs Plugin NAS session
 * \param[in] params Extended Stat File parameters
 * 
 * \returns VixError
 *
 *-----------------------------------------------------------------------------
 */

VixError
ExampleNasGetXStats(exNasPluginSession *session, 
                    VixDiskLibNasPluginStatXParams *params)
{
   VixDiskLibNasPluginStatXResult* statXResult =
      (VixDiskLibNasPluginStatXResult*) params->common.result;
   char *filePath;
   nfs_fh fh;
   fattr attributes;
   VixError status;

   Log(LGPFX" request for stats of '%s' \n", params->fileName);

   if (strncmp(params->fileName, session->localMountPoint, 
               session->localMPLen) != 0) {
      return VIX_E_INVALID_ARG;
   }

   /*
    * Get path relative to the local mount point
    */
   filePath = &params->fileName[session->localMPLen + 1];

   /*
    * lookup file handle
    */
   status = ExampleNasLookupFH(session, filePath, FALSE, 0, &fh, &attributes);
   if (status != VIX_OK) {
      return status;
   }

   statXResult->totalBytes = attributes.size; 
   statXResult->allocedBytes = attributes.blocks * VIXDISKLIB_SECTOR_SIZE;
   /*
    * NFS does not provide us with uniqueBytes, so assume that the file is not
    * thin provisioned and that all allocated bytes are unique.
    */
   statXResult->uniqueBytes =  statXResult->allocedBytes;

   return VIX_OK;
}


/*
 *-----------------------------------------------------------------------------
 * ExampleNasReserveSpace --                                             */ /**
 * 
 * \ingroup EXAMPLE_NAS_PLUGIN
 * \brief Execute Reserve Space primitive
 * 
 * \param[in] session Nfs Plugin NAS session
 * \param[in] resSpaceParams Reserve Space parameters
 * 
 * \returns VixError
 *
 *-----------------------------------------------------------------------------
 */

VixError
ExampleNasReserveSpace(exNasPluginSession *session,
                       VixDiskLibNasPluginResvSpaceParams *resSpaceParams)
{
   char *filePath;
   nfs_fh nfsFH;
   fattr attributes;
   VixError status;
   uint64 len, offset, size;
   uint64 lastReportedOffset;

   Log(LGPFX" request to reserve space for '%s'.\n", resSpaceParams->fileName);

   if (strncmp(resSpaceParams->fileName, session->localMountPoint, 
               session->localMPLen) != 0) {
      return VIX_E_DISK_INVAL;
   }

   /*
    * Get path relative to the local mount point
    */
   filePath = &resSpaceParams->fileName[session->localMPLen + 1];

   /*
    * lookup file handle
    */
   status = ExampleNasLookupFH(session, filePath, FALSE, 0, &nfsFH, &attributes);
   if (status != VIX_OK) {
      return status;
   }

   /*
    * A hack to test VIX_E_DISK_FULL handling
    */
   if (strstr(filePath, "errorDiskFull") != NULL) {
      status = VIX_E_DISK_FULL;
      Log(LGPFX" DEBUG: Failing with error VIX_E_DISK_FULL (0x%x).\n", status);
      return status;
   }

   /*
    * The only way to reserve space with NFS2 is to write 0s.
    */
   size = attributes.size; 

   status = call_print_list(session->remoteIP, session->remoteMountPoint, filePath, size);

   if (status != VIX_OK) {
	   Log(LGPFX" Failed write to '%s', Error.\n", 
			   resSpaceParams->fileName);
	   return status;
   }

   return VIX_OK;
}


/*
 *-----------------------------------------------------------------------------
 * ExampleNas_SupportStatus --                                           */ /**
 * 
 * \ingroup EXAMPLE_NAS_PLUGIN
 * \brief Return VAAI primitive support status.
 * 
 * \param[in] sessionID Plugin sessionID
 * \param[in] primitiveID Primitive to get the support status for
 * 
 * \returns VixError
 *
 *-----------------------------------------------------------------------------
 */

static VixError
ExampleNas_SupportStatus(VixDiskLibNasPluginSessionID sessionID,
                         VixDiskLibNasPluginPrimitiveID primitiveID)
{
   VixError status;
   exNasPluginSession *session = GET_SESSION_FROM_ID(sessionID);

   ASSERT(session->magic == EXAMPLE_NAS_PLUGIN_SESS_MAGIC);

   /*
    * The exampleNas plugin supports all primitives. We trivially return
    * SUPPORTED for all primitives. A real plugin should do the necessary
    * checks required to ensure that a primitive is supported on the Filer.
    */
   switch(primitiveID) {
   case VIXDISKLIB_NASPLUGIN_PRIM_CLONEFILE:
   case VIXDISKLIB_NASPLUGIN_PRIM_STATX:
   case VIXDISKLIB_NASPLUGIN_PRIM_RESVSPACE:
      status =  VIX_OK;
      break;
   default:
      status =  VIX_E_NOT_SUPPORTED;
      break;
   }

   return status;
}
