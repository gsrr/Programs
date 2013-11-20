/*
 *      foobar.h - example skeleton driver header
 */

#ifndef _FOOBAR_H
#define _FOOBAR_H

#define FOOBAR_INIT_MINOR 0x00000001

#define FOOBAR_VERSION "1.0"
#define FOOBAR_BUFLEN 1024
#define FOOBAR_MINOR_NAME "xyzzy"

struct foobar_state {
    dev_info_t    *dip;          /* Opaque dev_info pointer */
    int           init_state;    /* See FOOBAR_INIT_* */
    kmutex_t      mutex;         /* driver lock */
    char          *buffer;       /* message buffer */
};

#endif /* #ifdef _FOOBAR_H */
