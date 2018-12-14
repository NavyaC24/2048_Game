#include "GameLogic.hpp"
#include "stdlib.h"
#include "string.h"
#include <string>

using namespace std;

ColorMap colorMap = {{2, Red}, {4, Lime}, {8, Blue}, {16, Pink}, {32, Cyan}, {64, Red},
                     {128, Lime}, {256, Blue}, {512, Pink}, {1024, Cyan}, {2048, Green},
                     {4096, Red}, {8192, Lime}};

Game::Game(DisplayApp *app, Input *gameInput)
{
    displayApp = app;
    score = 0;
    moved = false;
    merged = false;
    input = gameInput;
    memset(grid, 0, sizeof(grid));
}

void Game::run()
{
    string title("GAME OVER");
    if(moveTiles(input->getDirection())) {
        generate();
    }

    updateGrid();

    if(!(merged || moved) && gridFull()) {
        //printf("Not merged AND Not moved");
        displayApp->displayString(title, Blue, 51, 4);
    }
}

bool Game::gridFull()
{
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(!grid[i][j]) {
                return false;
            }
        }
    }

    return true;
}

void Game::updateGrid()
{
    displayApp->displayGrid(grid, colorMap);
    displayScore();
}

void Game::displayScore()
{
    string title("SCORE");
    displayApp->drawBox(15, 30, 47, 49, Red);
    displayApp->displayString(title, Blue, 32, 18);
    displayApp->displayNumber(score, Green, 41, 18, BigFont);
}

bool Game::moveTiles(Directions direction)
{
    moved = false;
    merged = false;

    printf("Before: Merged: %d\n",merged);
    printf("Before: Moved: %d\n",moved);
    if(direction == Up) {
        moveUp();
    } else if(direction == Down) {
        moveDown();
    } else if(direction == Left) {
        moveLeft();
    } else if(direction == Right) {
        moveRight();
    }

    printf("After: Merged: %d\n",merged);
    printf("After: Moved: %d\n",moved);
    return moved;
}

void Game::rotate()
{
    int temp[4][4];

    for(int i = 0; i < 4 ; i++) {
        for(int j = 0; j < 4; j++) {
            temp[j][i] = grid[i][j];
        }
    }

    memcpy(grid, temp, sizeof(grid));
}

void Game::generate()
{
    int no,k,l;
    bool generated = false;

    while(!generated){
        k = rand() % 4;
        l = rand() % 4;
        if(grid[k][l] == 0) {
            no = 2 * ((rand() % 10) + 1);
            if(no < 5) {
                grid[k][l] = 4;
            } else {
                grid[k][l] = 2;
            }
            generated = true;
        }
    }
}

void Game::moveUp()
{
    int i , j, k, tmp;

    for(k = 0; k < 4; k++) {
        tmp = -1, j = 0;
        for(i = 0; i < 4; i++) {
            if(grid[i][k] != 0) {
                if(tmp == -1){
                    tmp = grid[i][k];
                } else if((tmp) && (grid[i][k] == tmp)) {
                    grid[j][k] = tmp + tmp;
                    score += grid[j][k];
                    tmp = -1;
                    j++;
                    merged = true;
                    moved = true;
                } else {
                    grid[j][k] = tmp;
                    tmp = grid[i][k];
                    j++;
                }
            }
        }
        if(tmp != -1) {
            grid[j][k] = tmp;
            j++;
        }
        while(j < 4) {
            if(grid[j][k]) {
                grid[j][k] = 0;
                moved = true;
            }
            j++;
        }
    }
}

void Game::moveDown()
{
    int i, j, k, tmp;

    for(k = 0; k < 4; k++)//column
    {
        tmp = -1, j = 3;
        for(i = 3; i >= 0; i--)//row
        {
            if(grid[i][k] != 0){
                if(tmp == -1){
                    tmp = grid[i][k];
                } else if((tmp) && (grid[i][k] == tmp)){
                    grid[j][k] = tmp + tmp;
                    score += grid[j][k];
                    tmp = -1;
                    j--;
                    merged = true;
                    moved = true;
                } else {
                    grid[j][k] = tmp;
                    tmp = grid[i][k];
                    j--;
                }
            }
        }
        if(tmp != -1) {
            grid[j][k] = tmp;
            j--;
        }
        while(j >= 0) {
            if(grid[j][k]) {
                grid[j][k] = 0;
                moved = true;
            }
            j--;
        }
    }
}

void Game::moveLeft()
{
    rotate();
    moveUp();
    rotate();
}

void Game::moveRight()
{
    rotate();
    moveDown();
    rotate();
}
