#include "GameLogic.hpp"
#include "stdlib.h"
#include "string.h"
#include <string>

using namespace std;

ColorMap colorMap = {{2, Red}, {4, Lime}, {8, Blue}, {16, Pink}, {32, Cyan}, {64, Red},
                     {128, Lime}, {256, Blue}, {512, Pink}, {1024, Cyan}, {2048, Green}};

Game::Game(DisplayApp *app, Input *gameInput)
{
    displayApp = app;
    score = 0;
    moved = false;
    input = gameInput;
    memset(grid, 0, sizeof(grid));
}

void Game::run()
{
    if(moveTiles(input->getDirection())) {
        generate();
    }
    updateGrid();
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
    if(direction == Up) {
        return moveUp();
    } else if(direction == Down) {
        return moveDown();
    } else if(direction == Left) {
        return moveLeft();
    } else if(direction == Right) {
        return moveRight();
    } else {
        moved = false;
    }

    return moved;
}

void Game::rotate()
{
    int i,j;
    int temp[4][4] = {0};

    for(i = 0; i <= 3 ; i++) {
        for(j = 0; j <= 3; j++) {
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

bool Game::moveUp()
{
    int i , j, k, tmp;
    moved = false;

    for(k = 0; k < 4; k++) {
        tmp = -1, j = 0;
        for(i = 0; i < 4; i++) {
            if(grid[i][k] != 0) {
                if(tmp == -1){
                    tmp = grid[i][k];
                } else if(grid[i][k] == tmp) {
                    grid[j][k] = tmp + tmp;
                    score += grid[j][k];
                    tmp = -1;
                    j++;
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
            moved = true;
        }
        while(j < 4) {
            grid[j][k] = 0;
            j++;
        }
    }
    return moved;
}

bool Game::moveDown()
{
    int i, j, k, tmp;
    moved = false;

    for(k = 0; k < 4; k++)//column
    {
        tmp = -1, j=3;
        for(i=3; i>=0; i--)//row
        {
            if(grid[i][k] != 0){
                if(tmp == -1){
                    tmp = grid[i][k];
                } else if(grid[i][k] == tmp){
                    grid[j][k] = tmp + tmp;
                    score= score+grid[j][k];
                    tmp = -1;
                    j--;
                    moved = true;
                } else {
                    grid[j][k] = tmp;
                    tmp = grid[i][k];
                    j--;
                }
            }
        }
        if(tmp != -1){
            grid[j][k] = tmp;
            j--;
            moved = true;
        }
        while(j >= 0){
            grid[j][k] = 0;
            j--;
        }
    }

    return moved;
}

bool Game::moveLeft()
{
    rotate();
    moveUp();
    rotate();
    return moved;
}

bool Game::moveRight()
{
    rotate();
    moveDown();
    rotate();
    return moved;
}
