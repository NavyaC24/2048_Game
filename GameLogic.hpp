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
private:
    int grid[4][4];
    int score;
    bool moved;
    DisplayApp *displayApp;
    Input *input;

public:
    Game(DisplayApp *displayApp, Input *gameInput);
    void updateScreen();
    void run();
    void generateNewTile();
    bool moveTiles(Direction inputDirection);
    void displayScore();
    void rotate();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    bool gridIsFull();
    bool anyPairsPresent();
    bool gameEnded();
};

#endif
