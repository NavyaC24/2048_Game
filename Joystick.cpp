/*
 * Joystick.cpp
 *
 *  Created on: Dec 8, 2018
 *      Author: Vishal
 */
#include "Joystick.hpp"
#include "LPC17xx.h"
#include "adc0.h"

Joystick::Joystick(Pin pinX, Pin pinY)
{
    channelX = getChannelNumberOfPin(pinX);
    channelY = getChannelNumberOfPin(pinY);
    selectPin(pinX);
    selectPin(pinY);
}

void Joystick::selectPin(Pin pin)
{
    switch(pin) {
    case k0_25:
        LPC_PINCON->PINSEL1 &= ~(3 << 18);
        LPC_PINCON->PINSEL1 |= (1 << 18);
        break;
    case k0_26:
        LPC_PINCON->PINSEL1 &= ~(3 << 20);
        LPC_PINCON->PINSEL1 |= (1 << 20);
        break;
    case k1_30:
        LPC_PINCON->PINSEL3 &= ~(3 << 28);
        LPC_PINCON->PINSEL3 |= (3 << 28);
        break;
    case k1_31:
        LPC_PINCON->PINSEL3 &= ~(3 << 30);
        LPC_PINCON->PINSEL3 |= (3 << 30);
        break;
   }
}
uint8_t Joystick::getChannelNumberOfPin(Pin pin)
{
    return pin + 2;  //Check the enum
}

uint16_t Joystick::getX()
{
    return adc0_get_reading(channelX);
}

uint16_t Joystick::getY()
{
    return adc0_get_reading(channelY);
}
