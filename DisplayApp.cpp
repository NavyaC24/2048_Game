/*
 * DisplayApp.cpp
 *
 *  Created on: Dec 4, 2018
 *      Author: Vishal
 */
#include "DisplayApp.hpp"
#include "string.h"
#include "stdint.h"
#include "string.h"
#include <stdio.h>

char digit_designs[][5][3] = {    {1,1,1,    //0
                                   1,0,1,
                                   1,0,1,
                                   1,0,1,
                                   1,1,1},

                                  {0,1,0,   //1
                                   1,1,0,
                                   0,1,0,
                                   0,1,0,
                                   1,1,1},

                                  {1,1,0,    //2
                                   0,0,1,
                                   0,1,0,
                                   1,0,0,
                                   1,1,1},

                                  {1,1,0,    //3
                                   0,0,1,
                                   0,1,0,
                                   0,0,1,
                                   1,1,0},

                                  {0,0,1,    //4
                                   0,1,1,
                                   1,0,1,
                                   1,1,1,
                                   0,0,1},

                                  {1,1,1,    //5
                                   1,0,0,
                                   0,1,0,
                                   0,0,1,
                                   1,1,1},

                                  {0,1,1,    //6
                                   1,0,0,
                                   1,1,1,
                                   1,0,1,
                                   0,1,1},

                                  {1,1,1,    //7
                                   0,0,1,
                                   0,1,0,
                                   1,0,0,
                                   1,0,0},

                                  {0,1,0,    //8
                                   1,0,1,
                                   1,1,1,
                                   1,0,1,
                                   0,1,0},

                                  {1,1,0,    //9
                                   1,0,1,
                                   1,1,1,
                                   0,0,1,
                                   1,1,0}};

int reverseNumber(int num)
{
    int rev = 0;
    while(num) {
        rev = (rev * 10) + (num % 10);
        num /= 10;
    }

    return rev;
}

void DisplayApp::initDisplay(LEDMatrixDisplayPincon &pincon)
{
    display.init(pincon);
}

void DisplayApp::updateDisplay()
{
    display.updateDisplay();
}

void DisplayApp::paintGridBorders(Colors color)
{
    uint64_t columns_borders = 0x0001000100010000;
    uint64_t row_borders = 0xFFFFFFFFFFFFFFFE;
    for(int i = 0; i < 23; i++) {
        if((i == 5) || (i == 11) || (i == 17)) {
            display.setRowData(i, color, row_borders);
        } else {
            display.setRowData(i, color, columns_borders);
        }
    }
}

void DisplayApp::paintOneDigit(int digit, Colors color, int start_row, int start_pixel)
{
    int row, pixel;

    for(int i = 0; i < 5; i++) {
        row = start_row + i;
        for(int j = 0; j < 3; j++) {
            pixel = 63 - (start_pixel + j);
            (digit_designs[digit][i][j]) ? display.setPixel(row, pixel, color) : display.clearPixel(row, pixel);
        }
    }
}

void DisplayApp::paintOneBlock(int num, Colors color, int start_row, int start_pixel)
{
    num = reverseNumber(num);
    while(num) {
        paintOneDigit(num % 10, color, start_row, start_pixel);
        start_pixel += 4;   //Each digit takes up 3 columns +1 blank space
        num /= 10;
    }
}

void DisplayApp::paintGrid(int (*grid)[4], ColorMap &colorMap)
{
    int start_row, start_pixel;

    display.clearFrameBuffers();
    paintGridBorders(White);
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            start_row = i * 6;    //New block at every 6th row
            start_pixel = j * 16; //New block at every 16th Column
            paintOneBlock(grid[i][j], colorMap[grid[i][j]], start_row, start_pixel);
        }
    }
}
