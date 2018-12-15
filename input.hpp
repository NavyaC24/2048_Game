/*
 * input.hpp
 *
 *  Created on: Dec 13, 2018
 *      Author: Vishal
 */
#ifndef INPUT_HPP
#define INPUT_HPP

enum Direction {
        Still,
        Up,
        Down,
        Right,
        Left
};

class Input {
public:
    virtual Direction getDirection() = 0;
    virtual bool selectPressed() = 0;
};

#endif
