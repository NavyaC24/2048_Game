/*
 * GameLogic.hpp
 *
 *  Created on: Nov 20, 2018
 *      Author: Team 2048
 */

#ifndef GAME_HPP
#define GAME_HPP

#include "DisplayApp.hpp"
#include "input.hpp"

class Game {
    public:
        int grid[4][4];
        int score;
        bool moved;
        DisplayApp *displayApp;
        Input *input;

    public:
        Game(DisplayApp *displayApp, Input *gameInput);
        void updateGrid();
        void run();
        void displayScore();
        bool moveTiles(Directions inputDirection);
        void rotate();
        void generate();
        bool moveUp();
        bool moveDown();
        bool moveLeft();
        bool moveRight();
};

#endif
