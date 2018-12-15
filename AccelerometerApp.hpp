/*
 * AccelerometerApp.hpp
 *
 *  Created on: Dec 13, 2018
 *      Author: Vishal
 */
#ifndef ACCELEROMETER_APP_HP
#define ACCELEROMETER_APP_HP

#include "input.hpp"
#include "io.hpp"

class AccelerometerApp : public Input {
private:
    Acceleration_Sensor acc_sense = Acceleration_Sensor::getInstance();

public:
    Direction getDirection();
    bool selectPressed();
    virtual ~AccelerometerApp();
};

#endif
