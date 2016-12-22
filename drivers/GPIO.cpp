/*
 * GPIO.cpp
 *
 *  Created on: 17/09/2016
 *      Author: scottm
 */

#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "../os/PI.h"
#include "GPIO.h"

using namespace std;

const char * GPIO::exportFileName_ = "/sys/class/gpio/export";
const char * GPIO::unexportFileName_ = "/sys/class/gpio/unexport";
const char * GPIO::gpioName_ = "/sys/class/gpio/gpio";
const char * GPIO::directionName_ = "/direction";
const char * GPIO::valueName_ = "/value";


GPIO::GPIO (unsigned pin,
            Direction dir)
    : pin_(pin),
      direction_(dir),
      exported_(false)
{
    if (pin > 26)
    {
        PI_LOG(true, "Invalid pin %d", pin);
        return;
    }

    // Export pin
    ofstream file(exportFileName_);
    if (file < 0)
    {
        PI_LOG(true, "Failed to open export file '%s'", exportFileName_);
        return;
    }

    // Set the direction for the pin
    file << pin;
    file.flush();
    file.close();

    PI::sleep(100);

    stringstream ss;
    ss << gpioName_ << pin << directionName_;
    string fname = ss.str();
    file.open(fname.c_str());

    if (file < 0)
    {
        PI_LOG(true, "Failed to open file %s", fname.c_str());
        return;
    }

    switch (dir)
    {
        case INPUT:
            PI_LOG(false, "Setting pin %d to input (%s)", pin, fname.c_str());
            file << "in";
            break;

        case OUTPUT:
            PI_LOG(false, "Setting pin %d to output (%s)", pin, fname.c_str());
            file << "out";
            break;
    }

    file.flush();
    file.close();
    PI::sleep(100);
    exported_ = true;
}

GPIO::~GPIO ()
{
    if (exported_)
    {
        ofstream file(unexportFileName_);
        if (file < 0)
        {
            PI_LOG(true, "Failed to open unexport file '%s'", unexportFileName_);
            return;
        }

        file << pin_;
        file.close();
    }
}

bool
GPIO::read()
{
    stringstream ss;
    ss << gpioName_ << pin_ << valueName_;
    string fname = ss.str();
    ifstream file(fname.c_str());

    if (file < 0)
    {
        PI_LOG(true, "Failed to open input file %s", fname.c_str());
        return (false);
    }

    string value;
    file >> value;
    file.close();

    int intVal = atoi(value.c_str());
    return (intVal > 0);
}

void
GPIO::write(bool value)
{
    stringstream ss;
    ss << gpioName_ << pin_ << valueName_;
    string fname = ss.str();
    ofstream file(fname.c_str());

    if (file < 0)
    {
        PI_LOG(true, "Failed to open input file %s", fname.c_str());
        return;
    }

    string valStr = value ? "1" : "0";
    file << valStr.c_str();
    file.close();
}

void
GPIO::write(unsigned long frequency,
            unsigned long duration)
{
    unsigned long delay = frequency == 0 ? 0 : 1000000 / frequency / 2;
    unsigned long cycles = frequency * duration / 1000;

    for (unsigned long i = 0; i < cycles; ++i)
    {
        write(true);
        usleep(delay);
        write(false);
        usleep(delay);
    }
}
