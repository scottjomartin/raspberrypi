/*
 * main.cpp
 *
 * This is a simple application for driving a piezo buzzer, connected to pin
 * 22. It plays the Mario brothers theme tune.
 *
 *  Created on: 22/12/2016
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

GPIO *pBuzzer = NULL;

const unsigned long NOTE_A[]    = { 29, 55, 110, 220, 440, 880, 1760, 3520 };
const unsigned long NOTE_AS[]   = { 30, 58, 117, 233, 466, 932, 1865, 3729 };
const unsigned long NOTE_B[]    = { 31, 62, 123, 247, 494, 988, 1976, 3951 };
const unsigned long NOTE_C[]    = { 33, 65, 131, 262, 523, 1047, 2093, 4186 };
const unsigned long NOTE_CS[]   = { 35, 69, 139, 277, 554, 1109, 2217, 4435 };
const unsigned long NOTE_D[]    = { 37, 73, 147, 294, 587, 1175, 2349, 4699 };
const unsigned long NOTE_DS[]   = { 39, 78, 156, 311, 622, 1245, 2489, 4435 };
const unsigned long NOTE_E[]    = { 41, 82, 165, 330, 659, 1319, 2637 };
const unsigned long NOTE_F[]    = { 44, 87, 175, 249, 698, 1397, 2794 };
const unsigned long NOTE_FS[]   = { 46, 93, 185, 370, 740, 1480, 2960 };
const unsigned long NOTE_G[]    = { 49, 98, 196, 392, 784, 1568, 3136 };
const unsigned long NOTE_GS[]   = { 52, 104, 208, 415, 831, 1661, 3322 };

typedef struct
{
    unsigned long frequency;
    unsigned long duration;
} Note;

const Note Mario[] = {
        { NOTE_E[6], 100 }, { NOTE_E[6], 100 }, { 0, 100 },         { NOTE_E[6], 100 },
        { 0, 100 },         { NOTE_C[6], 100 }, { NOTE_E[6], 100 }, { 0, 100 },
        { NOTE_G[6], 100 }, { 0, 100 },         { 0, 100 },         { 0, 100 },
        { NOTE_G[5], 100 }, { 0, 100 },         { 0, 100 },         { 0, 100 },

        { NOTE_C[6], 100 }, { 0, 100 },         { 0, 100 },         { NOTE_G[5], 100 },
        { 0, 100 },         { 0, 100 },         { NOTE_E[5], 100 }, { 0, 100 },
        { 0, 100 },         { NOTE_A[6], 100 }, { 0, 100 },         { NOTE_B[6], 100 },
        { 0, 100 },         { NOTE_AS[6], 100 },{ NOTE_A[6], 100 }, { 0, 100 },

        { NOTE_G[5], 75 },  { NOTE_E[6], 75 },  { NOTE_G[6], 75 },
        { NOTE_A[7], 100 }, { 0, 100 },         { NOTE_F[6], 100 }, { NOTE_G[6], 100 },
        { 0, 100 },         { NOTE_E[6], 100 }, { 0, 100 },         { NOTE_C[6], 100 },
        { NOTE_D[6], 100 }, { NOTE_B[6], 100 }, { 0, 100 },         { 0, 100 },

        { NOTE_C[6], 100 }, { 0, 100 },         { 0, 100 },         { NOTE_G[5], 100 },
        { 0, 100 },         { 0, 100 },         { NOTE_E[5], 100 }, { 0, 100 },
        { 0, 100 },         { NOTE_A[6], 100 }, { 0, 100 },         { NOTE_B[6], 100 },
        { 0, 100 },         { NOTE_AS[6], 100 },{ NOTE_A[6], 100 }, { 0, 100 },

        { NOTE_G[5], 75 },  { NOTE_E[6], 75 },  { NOTE_G[6], 75 },
        { NOTE_A[7], 100 }, { 0, 100 },         { NOTE_F[6], 100 }, { NOTE_G[6], 100 },
        { 0, 100 },         { NOTE_E[6], 100 }, { 0, 100 },         { NOTE_C[6], 100 },
        { NOTE_D[6], 100 }, { NOTE_B[6], 100 }, { 0, 100 },         { 0, 100 },
};

static void
shutdown(int signum)
{
    PI_LOG(true, "Shutting down");

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

    pTask = new PI_Task("PIEZOAPP");
    pTask->setShutdownHander(shutdown);

    pBuzzer = new GPIO(22, GPIO::OUTPUT);

    int numNotes = sizeof(Mario) / sizeof(Note);

    while (true)
    {
        for (int i = 0; i < numNotes; ++i)
        {
            pBuzzer->write(Mario[i].frequency, Mario[i].duration);
            PI::sleep(100);
        }
    }

    // Shouldn't ever get here

    return (0);
}

