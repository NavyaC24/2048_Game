/*
 * Joystick.hpp
 *
 *  Created on: Dec 8, 2018
 *      Author: Vishal
 */
#ifndef JOYSTICK_HPP
#define JOYSTICK_HPP

#include "stdint.h"

enum Pin {
        k0_25,       // AD0.2 <-- Light Sensor -->
        k0_26,       // AD0.3
        k1_30,       // AD0.4
        k1_31,       // AD0.5
};

class Joystick {
private:
    uint8_t channelX, channelY;

public:
    Joystick(Pin pinX, Pin pinY);
    void selectPin(Pin pin);
    uint8_t getChannelNumberOfPin(Pin pin);
    uint16_t getX();
    uint16_t getY();
};

#endif
