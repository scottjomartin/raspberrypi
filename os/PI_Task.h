/*
 * PI_Task.h
 *
 *  Created on: 01/10/2016
 *      Author: scottm
 */

#ifndef OS_PI_TASK_H_
#define OS_PI_TASK_H_

/**
 * This class can be used by tasks in order to set up the syslog, as well as
 * set up signal handlers for the SIGINT (kill) and SIGUSR1 (toggle debug)
 * signals.
 */
class PI_Task
{
public:
    /**
     *  @brief  Constructor
     *
     *  @param  Task name used in syslog messages
     */
    PI_Task (const char *taskName);

    virtual ~PI_Task ();

    void    setShutdownHander(void (*handler)(int));
};

#endif /* OS_PI_TASK_H_ */
