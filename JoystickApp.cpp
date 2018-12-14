/*
 * JoystickApp.cpp
 *
 *  Created on: Dec 8, 2018
*/
#include "JoystickApp.hpp"
#include "stdio.h"

JoystickApp::JoystickApp(uint8_t Xchannel, uint8_t Ychannel, Pins pinX, Pins pinY)
{
    JS = new Joystick(Xchannel, Ychannel, pinX, pinY);
}

Directions JoystickApp::getDirection()
{
    uint16_t x,y;

    x = JS->getX();
    y = JS->getY();

    if (x < 10) {
        return Left;
    } else if (x > 4000) {
        return Right;
    } else if (y < 10) {
        return Down;
    } else if (y > 4000) {
        return Up;
    }

    return Still;
}

bool JoystickApp::selectPressed()
{
    bool selected = false;
    Directions dir = getDirection();

    if(dir == Right || dir == Left) {
        selected = true;
    }

    return selected;
}

JoystickApp::~JoystickApp()
{
    delete JS;
}
