/*
 * AccelerometerApp.cpp
 *
 *  Created on: Dec 13, 2018
 *      Author: Vishal
 */

#include "AccelerometerApp.hpp"
#include "stdint.h"

Direction AccelerometerApp::getDirection()
{
    Direction direction;
    int16_t x = acc_sense.getX();
    int16_t y = acc_sense.getY();

    if(x > 120){
        direction = Right;
    } else if(x < -120){
        direction = Left;
    } else if(y < -120){
        direction = Up;
    } else if(y > 120){
        direction = Down;
    } else {
        direction = Still;
    }

    return direction;
}

bool AccelerometerApp::selectPressed()
{
    bool selected = false;
    Direction dir = getDirection();

    if(dir == Right || dir == Left) {
        selected = true;
    }

    return selected;
}

AccelerometerApp::~AccelerometerApp()
{
    //Nothing to do. Just chill!
}
