/*
 * DisplayApp.hpp
 *
 *  Created on: Dec 4, 2018
 *      Author: Vishal
 */

#ifndef DISPLAY_APP_HPP
#define DISPLAY_APP_HPP

#include "stdint.h"
#include "LEDMatrix.hpp"
#include <map>
#include <vector>
#include <string>

using namespace std;
typedef std::map<int, Color> ColorMap;

void getDigitsFromNumber(int num, std::vector<int>&digits);

enum FontType {
    SmallFont,
    BigFont
};

class DisplayApp {
private:
    LEDMatrix display = LEDMatrix::getInstance();

public:
    void initDisplay(LEDMatrixDisplayPincon &pincon);
    void updateDisplay();
    void displayGrid(int (*grid)[4], ColorMap &colorMap);
    void displayGridBorders(Color color);
    void displayNumber(int num, Color color, int start_row, int start_pixel, FontType font);
    void displayDigit(int digit, Color color, int start_row, int start_pixel, FontType font);
    void displayString(string s, Color color, int start_row, int start_pixel);
    void displayCharacter(char c, Color color, int start_row, int start_pixel);
    void displayNumberSmallFont(int num, Color color, int start_row, int start_pixel);
    void displayNumberBigFont(int num, Color color, int start_row, int start_pixel);
    void displayDigitSmallFont(int digit, Color color, int start_row, int start_pixel);
    void displayDigitBigFont(int digit, Color color, int start_row, int start_pixel);
    void drawBox(int xMin, int yMin, int xMax, int yMax, Color color);
};

#endif
