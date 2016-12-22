/*
 * PI.h
 *
 *  Created on: 19/09/2016
 *      Author: scottm
 */

#ifndef PI_H_
#define PI_H_

#include <unistd.h>


class PI
{
public:

    /**
     * @brief   Open the syslog.
     *
     * This method opens the syslog file for logging.
     *
     * @param   ident   Identifier to prefix syslog messages with
     */
    static void syslogOpenLog(const char *ident);

    /**
     * @brief   Close the syslog.
     *
     * This method closes the syslog, if it is open.
     */
    static void syslogClose();

    /**
     * @brief   Log an information message to the system log.
     *
     * This message write a syslog message, using the specified printf style
     * format string and variable arguments.
     *
     * @param   always  Whether to print to the message always or only in debug mode
     * @param   format  A printf format string
     * @param   ...     Variable arguments consistent with format string
     *
     * @pre     format != NULL
     */
    static void syslogMessage(bool always, const char *format, ...);

    /**
     * @brief   Toggle the debug mode.
     *
     * This method is designed as a callback for signal handling, allowing
     * debug mode to be toggled on and off.
     */
    static void toggleDebug(int signum);

    /**
     * @brief   Sleep for a period defined in ms.
     *
     * @param   ms  The sleep time in milli-seconds
     */
    static void sleep(int ms);

private:
    /**
     * Records whether the log file has been opened.
     */
    static bool         isLogOpen_;

    /**
     * Records whether debug mode is active.
     */
    static bool         isLogDebug_;
};


#define PI_LOG          PI::syslogMessage
#define PI_OPENLOG      PI::syslogOpenLog
#define PI_CLOSELOG     PI::syslogClose

#endif /* PI_H_ */
