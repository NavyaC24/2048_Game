/*
 * GameLogic.cpp
 *
 *  Created on: Nov 26, 2018
 *      Author: Vishal
 */

#include "GameLogic.hpp"
#include "stdlib.h"
#include "string.h"

ColorMap colorMap = {{2, Red}, {4, Lime}, {8, Blue}, {16, Pink}, {32, Cyan}, {64, Red},
                     {128, Lime}, {256, Blue}, {512, Pink}, {1024, Cyan}, {2048, Green}};

Game::Game(DisplayApp *app)
{
    displayApp = app;
    score = 0;
    memset(grid, 0, sizeof(grid));
}

void Game::updateGrid()
{
    displayApp->paintGrid(grid, colorMap);
}

void Game::moveTiles(Directions direction)
{
    if(direction == Up) {
        moveUp();
    } else if(direction == Down) {
        moveDown();
    } else if(direction == Left) {
        moveLeft();
    } else if(direction == Right) {
        moveRight();
    }
}
