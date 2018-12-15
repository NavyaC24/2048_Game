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
#include <vector>

extern char small_digits[10][5][3];
extern char big_digits[10][7][5];
extern char big_letters[26][7][5];

void getDigitsFromNumber(int num, std::vector<int>&digits)
{
    do {
        digits.insert(digits.begin(), num % 10);
        num /= 10;
    } while(num);
}

void DisplayApp::initDisplay(LEDMatrixDisplayPincon &pincon)
{
    display.init(pincon);
}

void DisplayApp::updateDisplay()
{
    display.updateDisplay();
}

void DisplayApp::displayGridBorders(Color color)
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

void DisplayApp::displayNumber(int number, Color color, int start_row, int start_pixel, FontType font)
{
    if(font == SmallFont) {
        displayNumberSmallFont(number, color, start_row, start_pixel);
    } else if(font == BigFont) {
        displayNumberBigFont(number, color, start_row, start_pixel);
    } else {
        printf("Invalid Font Type\n");
    }
}

void DisplayApp::displayDigit(int digit, Color color, int start_row, int start_pixel, FontType font)
{
    if(font == SmallFont) {
        displayDigitSmallFont(digit, color, start_row, start_pixel);
    } else if(font == BigFont) {
        displayDigitBigFont(digit, color, start_row, start_pixel);
    } else {
        printf("Invalid Font Type\n");
    }
}

void DisplayApp::displayDigitSmallFont(int digit, Color color, int start_row, int start_pixel)
{
    int row, pixel;

    for(int i = 0; i < 5; i++) {
        row = start_row + i;
        for(int j = 0; j < 3; j++) {
            pixel = 63 - (start_pixel + j);
            (small_digits[digit][i][j]) ? display.setPixel(row, pixel, color) : display.clearPixel(row, pixel);
        }
    }
}

void DisplayApp::displayNumberSmallFont(int num, Color color, int start_row, int start_pixel)
{
    std::vector<int> digits;
    std::vector<int>::iterator it;

    getDigitsFromNumber(num, digits);
    for(it = digits.begin(); it != digits.end(); it++) {
        displayDigitSmallFont(*it, color, start_row, start_pixel);
        start_pixel += 4;   //Each digit takes up 3 columns +1 blank space
    }
}

void DisplayApp::displayDigitBigFont(int digit, Color color, int start_row, int start_pixel)
{
    int row, pixel;

    for(int i = 0; i < 7; i++) {
        row = start_row + i;
        for(int j = 0; j < 5; j++) {
            pixel = 63 - (start_pixel + j);
            (big_digits[digit][i][j]) ? display.setPixel(row, pixel, color) : display.clearPixel(row, pixel);
        }
    }
}

void DisplayApp::displayNumberBigFont(int num, Color color, int start_row, int start_pixel)
{
    std::vector<int> digits;
    std::vector<int>::iterator it;

    getDigitsFromNumber(num, digits);
    for(it = digits.begin(); it != digits.end(); it++) {
        displayDigitBigFont(*it, color, start_row, start_pixel);
        start_pixel += 6;   //Each digit takes up 5 columns +1 blank space
    }
}

void DisplayApp::displayGrid(int (*grid)[4], ColorMap &colorMap)
{
    int start_row, start_pixel;

    display.clearFrameBuffer();
    displayGridBorders(White);
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            start_row = i * 6;    //New block at every 6th row
            start_pixel = j * 16; //New block at every 16th Column
            displayNumberSmallFont(grid[i][j], colorMap[grid[i][j]], start_row, start_pixel);
        }
    }
}

void DisplayApp::drawBox(int xMin, int yMin, int xMax, int yMax, Color color)
{
    uint64_t row_data = 0xFFFFFFFFFFFFFFFF;
    row_data = (row_data << xMin) & (row_data >> (64 - xMax - 1));

    display.setRowData(yMin, color, row_data);
    display.setRowData(yMax, color, row_data);

    for(int i = yMin + 1; i < yMax; i++) {
        display.setPixel(i, xMin, color);
        display.setPixel(i, xMax, color);
    }
}

void DisplayApp::displayCharacter(char c, Color color, int start_row, int start_pixel)
{
    int row, pixel;

    for(int i = 0; i < 7; i++) {
        row = start_row + i;
        for(int j = 0; j < 5; j++) {
            pixel = 63 - (start_pixel + j);
            (big_letters[c - 65][i][j]) ? display.setPixel(row, pixel, color) : display.clearPixel(row, pixel);
        }
    }
}

void DisplayApp::displayString(string s, Color color, int start_row, int start_pixel)
{
    for(unsigned i = 0; i < s.size(); i++) {
        if(s[i] == ' ') {
            start_pixel += 5;
            continue;
        }

        displayCharacter(s[i], color, start_row, start_pixel);
        start_pixel += 6;
    }
}
