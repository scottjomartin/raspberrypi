/*
 * PI_Task.cpp
 *
 *  Created on: 01/10/2016
 *      Author: scottm
 */

#include <signal.h>

#include "PI_Task.h"
#include "PI.h"

PI_Task::PI_Task (const char *taskName)
{
    PI_OPENLOG(taskName);
    PI_LOG(true, "Starting");
    signal(SIGUSR1, PI::toggleDebug);
}

PI_Task::~PI_Task ()
{
    PI_LOG(true, "Finished");
    PI_CLOSELOG();
}

void
PI_Task::setShutdownHander(void (*handler)(int))
{
    signal(SIGTERM, handler);
}
