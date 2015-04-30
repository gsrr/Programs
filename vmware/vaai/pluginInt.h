/* **************************************************************************
 * Copyright 2010 VMware, Inc.  All rights reserved.
 * **************************************************************************/

/*
 * pluginInt.h --
 *
 */

#ifndef _PLUGININT_H_
#define _PLUGININT_H_

#include <assert.h>
#include <rpc/rpc.h>
#include "nfs_prot.h"
#include "mount.h"
#include <pthread.h>
#include "vixDiskLibNasPlugin.h"
#include "llist.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif


#define EXAMPLE_NAS_PLUGIN_SESS_MAGIC 0x1A5B6C7E9F193832LL
#define MS_PER_SEC 1000

#define LGPFX "ExampleNasPlugin:"
#define ASSERT assert

/*
 * Convert between session pointer and session ID
 * This is platform dependent
 */

struct exNasPluginSession;

#ifdef VM_X86_64
#define MAKE_SESSION_ID(session) ((VixDiskLibNasPluginSessionID) (session))
#define GET_SESSION_FROM_ID(sessionID) ((exNasPluginSession *) (sessionID))
#else
#define MAKE_SESSION_ID(session) ((VixDiskLibNasPluginSessionID) (uint32) (session))
#define GET_SESSION_FROM_ID(sessionID) ((exNasPluginSession *) (uint32) (sessionID))
#endif

// Mount protocol success 
#define MOUNT_OK 0

extern void Log(const char *fmt, ...);
extern void Warning(const char *fmt, ...);
extern void Panic(const char *fmt, ...);

extern VixDiskLibNasPlugin ExampleNasPlugin;

extern VixDiskLibPluginInit ExampleNas_PluginInit;
extern VixDiskLibPluginDone ExampleNas_PluginDone;

// global session list
extern pthread_mutex_t gSessionListLock;
extern struct exNasPluginSession *gSessionHead;

extern char gZeroBuf[NFS_MAXDATA];

typedef struct exNasPluginSession {
   uint64 magic;
   CLIENT *clnt;
   char *remoteIP;
   char *remoteMountPoint;
   char *localMountPoint;
   int  localMPLen;
   struct timeval timeout;
   fhandle rootFH;

   // global list linkage
   struct exNasPluginSession *next;
   struct exNasPluginSession *prev;


} exNasPluginSession;

#ifdef __cplusplus
}
#endif

#endif // _PLUGININT_H_
