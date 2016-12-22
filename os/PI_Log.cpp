/*
 * PI_Log.cpp
 *
 *  Created on: 19/09/2016
 *      Author: scottm
 */

#include <syslog.h>
#include <stdarg.h>
#include <unistd.h>
#include "PI.h"

bool PI::isLogOpen_ = false;
bool PI::isLogDebug_ = false;

void
PI::syslogOpenLog(const char *ident)
{
    if (!isLogOpen_)
    {
        openlog(ident, LOG_CONS | LOG_PID, LOG_LOCAL0);
        isLogOpen_ = true;
    }
}

void
PI::syslogClose()
{
    closelog();
    isLogOpen_ = false;
}

void
PI::syslogMessage(bool always, const char *format, ...)
{
    if (isLogDebug_ || always)
    {
        va_list ap;

        // Open the log if not already open
        if (!isLogOpen_)
            syslogOpenLog("");

        va_start(ap, format);
        vsyslog(LOG_INFO, format, ap);
        va_end(ap);
    }
}

void
PI::toggleDebug(int signum)
{
    isLogDebug_ = !isLogDebug_;
    PI_LOG(true, "Debug toggled to %d", isLogDebug_);
}

void
PI::sleep(int ms)
{
    usleep(ms*1000);
}
