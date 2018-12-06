/*
 * GameLogic.hpp
 *
 *  Created on: Nov 20, 2018
 *      Author: Vishal
 */

#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP

#include "DisplayApp.hpp"

class GameLogic {
    public:
        int grid[4][4];
        DisplayApp *displayApp;

    public:
        GameLogic(DisplayApp *displayApp);
        void updateGrid();
};

#endif
