/*
 * Joystick.hpp
 *
 *  Created on: Dec 8, 2018
 *      Author: Vishal
 */
#ifndef JOYSTICK_HPP
#define JOYSTICK_HPP

#include "stdint.h"

enum Pins {
        k0_25,       // AD0.2 <-- Light Sensor -->
        k0_26,       // AD0.3
        k1_30,       // AD0.4
        k1_31,       // AD0.5
};

class Joystick {
private:
    uint8_t channelX, channelY;
public:
    Joystick(uint8_t channelX, uint8_t channelY, Pins pinX, Pins pinY);
    void selectPin(Pins pin);
    uint16_t getX();
    uint16_t getY();
};

#endif
