/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "nfs_prot.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

enum clnt_stat 
nfsproc_null_2(void *argp, void *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, NFSPROC_NULL,
		(xdrproc_t) xdr_void, (caddr_t) argp,
		(xdrproc_t) xdr_void, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
nfsproc_getattr_2(nfs_fh *argp, attrstat *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, NFSPROC_GETATTR,
		(xdrproc_t) xdr_nfs_fh, (caddr_t) argp,
		(xdrproc_t) xdr_attrstat, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
nfsproc_setattr_2(sattrargs *argp, attrstat *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, NFSPROC_SETATTR,
		(xdrproc_t) xdr_sattrargs, (caddr_t) argp,
		(xdrproc_t) xdr_attrstat, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
nfsproc_root_2(void *argp, void *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, NFSPROC_ROOT,
		(xdrproc_t) xdr_void, (caddr_t) argp,
		(xdrproc_t) xdr_void, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
nfsproc_lookup_2(diropargs *argp, diropres *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, NFSPROC_LOOKUP,
		(xdrproc_t) xdr_diropargs, (caddr_t) argp,
		(xdrproc_t) xdr_diropres, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
nfsproc_readlink_2(nfs_fh *argp, readlinkres *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, NFSPROC_READLINK,
		(xdrproc_t) xdr_nfs_fh, (caddr_t) argp,
		(xdrproc_t) xdr_readlinkres, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
nfsproc_read_2(readargs *argp, readres *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, NFSPROC_READ,
		(xdrproc_t) xdr_readargs, (caddr_t) argp,
		(xdrproc_t) xdr_readres, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
nfsproc_writecache_2(void *argp, void *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, NFSPROC_WRITECACHE,
		(xdrproc_t) xdr_void, (caddr_t) argp,
		(xdrproc_t) xdr_void, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
nfsproc_write_2(writeargs *argp, attrstat *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, NFSPROC_WRITE,
		(xdrproc_t) xdr_writeargs, (caddr_t) argp,
		(xdrproc_t) xdr_attrstat, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
nfsproc_create_2(createargs *argp, diropres *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, NFSPROC_CREATE,
		(xdrproc_t) xdr_createargs, (caddr_t) argp,
		(xdrproc_t) xdr_diropres, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
nfsproc_remove_2(diropargs *argp, nfsstat *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, NFSPROC_REMOVE,
		(xdrproc_t) xdr_diropargs, (caddr_t) argp,
		(xdrproc_t) xdr_nfsstat, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
nfsproc_rename_2(renameargs *argp, nfsstat *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, NFSPROC_RENAME,
		(xdrproc_t) xdr_renameargs, (caddr_t) argp,
		(xdrproc_t) xdr_nfsstat, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
nfsproc_link_2(linkargs *argp, nfsstat *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, NFSPROC_LINK,
		(xdrproc_t) xdr_linkargs, (caddr_t) argp,
		(xdrproc_t) xdr_nfsstat, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
nfsproc_symlink_2(symlinkargs *argp, nfsstat *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, NFSPROC_SYMLINK,
		(xdrproc_t) xdr_symlinkargs, (caddr_t) argp,
		(xdrproc_t) xdr_nfsstat, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
nfsproc_mkdir_2(createargs *argp, diropres *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, NFSPROC_MKDIR,
		(xdrproc_t) xdr_createargs, (caddr_t) argp,
		(xdrproc_t) xdr_diropres, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
nfsproc_rmdir_2(diropargs *argp, nfsstat *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, NFSPROC_RMDIR,
		(xdrproc_t) xdr_diropargs, (caddr_t) argp,
		(xdrproc_t) xdr_nfsstat, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
nfsproc_readdir_2(readdirargs *argp, readdirres *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, NFSPROC_READDIR,
		(xdrproc_t) xdr_readdirargs, (caddr_t) argp,
		(xdrproc_t) xdr_readdirres, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
nfsproc_statfs_2(nfs_fh *argp, statfsres *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, NFSPROC_STATFS,
		(xdrproc_t) xdr_nfs_fh, (caddr_t) argp,
		(xdrproc_t) xdr_statfsres, (caddr_t) clnt_res,
		TIMEOUT));
}
