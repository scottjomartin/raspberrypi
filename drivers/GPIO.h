/*
 * GPIO.h
 *
 *  Created on: 17/09/2016
 *      Author: scottm
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <string>

/**
 * @class       GPIO
 *
 * @brief       Allows control of a GPIO pin.
 */
class GPIO
{
public:

    enum Direction
    {
        INPUT,
        OUTPUT,
        PWM
    };

    /**
     * @brief   Constructor
     *
     * @param   pin     GPIO pin number
     * @param   dir     Direction for control (input/output)
     */
    GPIO (unsigned pin, Direction dir);

    /**
     * @brief   Destructor
     */
    virtual ~GPIO ();

    /**
     * @brief   Returns the value of an input pin.
     */
    bool        read();

    /**
     * @brief   Writes the value to an output pin.
     *
     * @param   value   Value to write to output pin
     */
    void        write(bool value);

    /**
     * @brief   Controls the output for a given frequency and duration. This is
     *          used to control a piezo buzzer.
     *
     * @param   frequency   The frequency to drive the buzzer
     * @param   duration    The duration for the note
     */
    void        write(unsigned long frequency, unsigned long duration);

private:
    /**
     * @brief   GPIO pin number
     */
    unsigned            pin_;

    /**
     * @brief   Defines whether this is an input or output
     */
    Direction           direction_;

    /**
     * @brief   Records whether the GPIO has been exported
     */
    bool                exported_;

    static const char * exportFileName_;
    static const char * unexportFileName_;
    static const char * gpioName_;
    static const char * directionName_;
    static const char * valueName_;
};

#endif /* GPIO_H_ */
