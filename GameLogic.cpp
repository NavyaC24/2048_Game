/*
 * GameLogic.cpp
 *
 *  Created on: Nov 26, 2018
 *      Author: Vishal
 */

#include "GameLogic.hpp"
#include "string.h"
#include <stdio.h>
#include "stdint.h"

uint8_t digits[][5][4] = {{0x06, 0x09, 0x09, 0x09, 0x06},  //0
                          {0x02, 0x06, 0x02, 0x02, 0x07},  //1
                          {0x0E, 0x01, 0x0F, 0x08, 0x0F},  //2
                          {0x0E, 0x01, 0x06, 0x01, 0x0E},  //3
                          {0x02, 0x06, 0x0F, 0x02, 0x02},  //4
                          {0x07, 0x08, 0x0F, 0x01, 0x0F},  //5
                          {0x0F, 0x08, 0x0F, 0x09, 0x06},  //6
                          {0x0F, 0x02, 0x04, 0x08, 0x08},  //7
                          {0x06, 0x09, 0x06, 0x09, 0x06},  //8
                          {0x06, 0x09, 0x0F, 0x01, 0x0E}}; //9

char digit_designs[][5][4] = {    {0,1,1,0,    //0
                                   1,0,0,1,
                                   1,0,0,1,
                                   1,0,0,1,
                                   0,1,1,0},

                                  {0,0,1,0,    //1
                                   0,1,1,0,
                                   0,0,1,0,
                                   0,0,1,0,
                                   0,1,1,1},

                                  {1,1,1,0,    //2
                                   0,0,0,1,
                                   1,1,1,1,
                                   1,0,0,0,
                                   1,1,1,1},

                                  {1,1,1,0,    //3
                                   0,0,0,1,
                                   0,1,1,0,
                                   0,0,0,1,
                                   1,1,1,0},

                                  {0,0,1,0,    //4
                                   0,1,1,0,
                                   1,1,1,1,
                                   0,0,1,0,
                                   0,0,1,0},

                                  {0,1,1,1,    //5
                                   1,0,0,0,
                                   1,1,1,1,
                                   0,0,0,1,
                                   1,1,1,1},

                                  {0,1,1,1,    //6
                                   1,0,0,0,
                                   1,1,1,1,
                                   1,0,0,1,
                                   0,1,1,0},

                                  {1,1,1,1,    //7
                                   0,0,1,0,
                                   0,1,0,0,
                                   1,0,0,0,
                                   1,0,0,0},

                                  {0,1,1,0,    //8
                                   1,0,0,1,
                                   0,1,1,0,
                                   1,0,0,1,
                                   0,1,1,0},

                                  {0,1,1,0,    //9
                                   1,0,0,1,
                                   1,1,1,1,
                                   0,0,0,1,
                                   1,1,1,0}};


void GameLogic::drawGridBorders()
{
    uint64_t columns_borders = 0x8001000200040008;
    uint64_t row_borders = 0xFFFFFFFFFFFFFFF8;
    for(int i = 0; i < 25; i++) {
        if(!(i % 6)) {
            display.setRowData(i, White, row_borders);
        } else {
            display.setRowData(i, White, columns_borders);
        }
    }
}

void GameLogic::translateGridToDisplayBuffer()
{
    char digit;
    dumpGridAsString();
    for(uint8_t i = 0; i < 25; i++) {
        for(int j = 0; j < 61; j++) {
            if(!(i % 6) || !(j % 15)) {  //This is a row separator in the grid; Making it white
                if(!(i % 6)) {
                    display.setRowData(i, White);
                } else {
                    display.setPixel(i, j, White);
                }
            } else {
                digit = grid_as_string[i / 6][j / 5];
                if(digit == ' ' || !(j % 5)) { //Line of separation between digits and empty spaces if no number to print in a block
                    display.clearPixel(i, j);
                }else {
                    printf("Setting row %d column %d red\n", i, j);
                    ((digit_designs[digit - '0'][(i % 6) - 1][(j % 5) - 1]) ? display.setPixel(i, j, Red) : display.clearPixel(i, j));
                }
            }
        }
    }
}

void GameLogic::dumpGridAsString()
{
    //Dump all numbers in the matrix as 4 strings of 12 digits each (one string for each row)
    //If there is no digit to print then put space in it's place (so the total string legth for a row is still 12)
    char num[4];
    for(int i = 0; i < 4; i++) {
        memset(grid_as_string[i], 0, 13);
        for(int j = 0; j < 4; j++) {
            if(game_grid[i][j] == 0) {
                sprintf(num, "%s%c", "   ", 0);
            }else if(game_grid[i][j] < 10) {
                sprintf(num, "%d%s%c", game_grid[i][j], "  ",0);
            }else if(game_grid[i][j] < 100) {
                sprintf(num, "%d%s%c", game_grid[i][j], " ",0);
            }else {
                sprintf(num, "%d%c", game_grid[i][j],0);
            }
            sprintf(&grid_as_string[i][j * 3], "%s", num);
        }
        grid_as_string[i][12] = '\0';
    }
}
