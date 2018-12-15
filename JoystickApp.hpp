/*
 * JoystickApp.hpp
 *
 *  Created on: Dec 8, 2018
 *      Author: Vishal
 */

#ifndef JOYSTICKAPP_HPP_
#define JOYSTICKAPP_HPP_

#include "Joystick.hpp"
#include "input.hpp"

class JoystickApp : public Input {
private:
    Joystick *JS;

public:
    virtual ~JoystickApp();
    JoystickApp(Pin pinX, Pin pinY);
    Direction getDirection();
    bool selectPressed();
};

#endif /* JOYSTICKAPP_HPP_ */
