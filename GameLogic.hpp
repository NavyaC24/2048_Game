/*
 * GameLogic.hpp
 *
 *  Created on: Nov 20, 2018
 *      Author: Vishal
 */

#ifndef GAME_HPP
#define GAME_HPP

#include "DisplayApp.hpp"
#include "JoystickApp.hpp"


class Game {
    public:
        int grid[4][4];
        int score;
        DisplayApp *displayApp;

    public:
        Game(DisplayApp *displayApp);
        void updateGrid();
        void run();
        void moveTiles(Directions inputDirection);
};

#endif
