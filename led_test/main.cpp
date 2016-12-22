/*
 * main.cpp
 *
 * This is a simple application that makes use of the GPIO pins as both inputs
 * and outputs. It uses pins 12, 16, 20 and 21 as inputs to drive LEDs, with
 * each LED being in series with a 270 ohm resister to ground. It then uses
 * pins 19 and 26 as inputs. The 3.3V rail is connected to a switch and then
 * to the input pin. Changing switch positions will change the way the LEDs
 * are driven.
 *
 *  Created on: 17/09/2016
 *      Author: scottm
 */


#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#include <drivers/GPIO.h>
#include <os/PI.h>
#include <os/PI_Task.h>

PI_Task *pTask = NULL;

static const int NUM_LEDS   = 4;
static const int NUM_SWITCHES = 2;

GPIO *pLed[NUM_LEDS] = { NULL, NULL, NULL, NULL };
GPIO *pSwitch[NUM_SWITCHES] = { NULL, NULL };
GPIO *pBuzzer = NULL;

static void
shutdown(int signum)
{
    PI_LOG(true, "Shutting down");

    for (int i = 0; i < NUM_LEDS; ++i)
        if (pLed[i] != NULL)
            delete (pLed[i]);

    for (int i = 0; i < NUM_SWITCHES; ++i)
        if (pSwitch[i] != NULL)
            delete (pSwitch[i]);

    if (pBuzzer != NULL)
        delete (pBuzzer);

    if (pTask != NULL)
        delete (pTask);

    exit(0);
}

int
main()
{
    int offCycles = 0;
    bool on = false;
    int sleepTime;

    pTask = new PI_Task("GPIO_TEST");
    pTask->setShutdownHander(shutdown);

    pLed[0] = new GPIO(12, GPIO::OUTPUT);
    pLed[1] = new GPIO(16, GPIO::OUTPUT);
    pLed[2] = new GPIO(20, GPIO::OUTPUT);
    pLed[3] = new GPIO(21, GPIO::OUTPUT);

    pSwitch[0] = new GPIO(19, GPIO::INPUT);
    pSwitch[1] = new GPIO(26, GPIO::INPUT);

    while (true)
    {
        bool sw1Pos = pSwitch[0]->read();
        bool sw2Pos = pSwitch[1]->read();

        if ((!sw1Pos) && (!sw2Pos))
        {
            // Turn off leds
            pLed[0]->write(false);
            pLed[1]->write(false);
            pLed[2]->write(false);
            pLed[3]->write(false);
            on = false;
            ++offCycles;
            sleepTime = 500;
        }
        else if ((sw1Pos) && (sw2Pos))
        {
            // Both switches are on
            pLed[0]->write(on);
            pLed[1]->write(on);
            pLed[2]->write(on);
            pLed[3]->write(on);
            on = !on;
            sleepTime = 500;
            offCycles = 0;
        }
        else
        {
            // One switch is on
            pLed[0]->write(on);
            pLed[1]->write(!on);
            pLed[2]->write(on);
            pLed[3]->write(!on);
            on = !on;
            sleepTime = sw1Pos ? 500 : 1000;
        }

        if (sleepTime > 0)
            PI::sleep(sleepTime);
    }

    // Shouldn't ever get here

    return (0);
}

