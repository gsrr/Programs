/* **************************************************************************
 * Copyright 2010 VMware, Inc.  All rights reserved.
 * **************************************************************************/

/*
 * This plugin implements an example loadable DiskLib plugin that uses SUN PRC
 * protocol to implement NAS plugin API primitives over NFS2.
 */

#include "pluginInt.h"

/* List of all plugins in this library */
static VixDiskLibNasPlugin *gPlugins[] = { &ExampleNasPlugin, NULL };

/* Usage counter for init/done functions */
static uint32 gUseCount = 0;

/* External symbol to be exported by shared lib. Contains plugin entrypoints. */
VixDiskLibPlugin **VixDiskLibPlugin_EntryPoint = (VixDiskLibPlugin **)gPlugins;

static VixDiskLibGenericLogFunc *pluginLog;
static VixDiskLibGenericLogFunc *pluginWarning;
static VixDiskLibGenericLogFunc *pluginPanic;


/*
 *-----------------------------------------------------------------------------
 *
 * ExampleNas_PluginInit --
 *
 *      Initialize plugin. Set up log functions.
 *
 * Results:
 *      VIX_OK on success, error otherwise
 *
 * Side effects:
 *
 *-----------------------------------------------------------------------------
 */

VixError
ExampleNas_PluginInit(VixDiskLibGenericLogFunc *log,
           VixDiskLibGenericLogFunc *warn,
           VixDiskLibGenericLogFunc *panic)
{
   if (gUseCount > 0) {
      /* Already initialized... */
      gUseCount += 1;
      return VIX_OK;
   }

   if (log == NULL || warn == NULL || panic == NULL) {
      return VIX_E_INVALID_ARG;
   }

   gUseCount += 1;

   pluginLog = log;
   pluginWarning = warn;
   pluginPanic = panic;

   memset(gZeroBuf, 0, sizeof(gZeroBuf));

   return VIX_OK;
}


/*
 *-----------------------------------------------------------------------------
 *
 * ExampleNas_PluginDone --
 *
 *      Prepare plugin for unload. No-Op.
 *
 * Results:
 *      None.
 *
 * Side effects:
 *      None.
 *
 *-----------------------------------------------------------------------------
 */

void
ExampleNas_PluginDone(void)
{
   gUseCount -= 1;

   if (gUseCount == 0) {
      // verify that all sessions are closed
      pthread_mutex_lock(&gSessionListLock);

      if (gSessionHead) {
         exNasPluginSession *sess;
         for(sess = gSessionHead; sess; sess = sess->next) {
            Warning(LGPFX" Session %p is active. \n", sess);
         }

         Panic(LGPFX" Some sessions are still active.");
      }

      pthread_mutex_unlock(&gSessionListLock);
   }
}


/*
 * Logging wrappers
 */

void
Log(const char *fmt, ...)
{
   va_list args;

   va_start(args, fmt);

   pluginLog(fmt, args);

   va_end(args);
}

void
Warning(const char *fmt, ...)
{
   va_list args;

   va_start(args, fmt);

   pluginWarning(fmt, args);

   va_end(args);
}

void
Panic(const char *fmt, ...)
{
   va_list args;

   va_start(args, fmt);

   pluginPanic(fmt, args);

   va_end(args);
}

