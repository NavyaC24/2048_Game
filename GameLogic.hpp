/*
 * GameLogic.hpp
 *
 *  Created on: Nov 20, 2018
 *      Author: Vishal
 */

#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP

#include "stdint.h"
#include "LEDMatrix.hpp"

class GameLogic {
    private:
        LEDMatrix display = LEDMatrix::getInstance();
        int game_grid[4][4] = {{512, 512, 512, 512},
                               {512, 512, 512, 512},
                               {512, 512, 512, 512},
                               {512, 512, 512, 512}};
        char grid_as_string[4][13];

    public:
        void displayStartScreen();
        void displayEndScreen();
        void drawGridBorders();
        void translateGridToDisplayBuffer();
        void dumpGridAsString();
};

#endif
