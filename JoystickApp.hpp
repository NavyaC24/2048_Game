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
public:
    virtual ~JoystickApp();
    JoystickApp(uint8_t Xchannel, uint8_t Ychannel, Pins pinX, Pins pinY);
    Directions getDirection();
    bool selectPressed();
private:
    Joystick *JS;
};

#endif /* JOYSTICKAPP_HPP_ */
