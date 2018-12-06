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

typedef std::map<int, Colors> ColorMap;

class DisplayApp {
    private:
        LEDMatrix display = LEDMatrix::getInstance();

    public:
        void initDisplay(LEDMatrixDisplayPincon &pincon);
        void updateDisplay();
        void displayStartScreen();
        void displayEndScreen();
        void paintGrid(int (*grid)[4], ColorMap &colorMap);
        void paintGridBorders(Colors color);
        void paintOneBlock(int num, Colors color, int start_row, int start_pixel);
        void paintOneDigit(int digit, Colors color, int start_row, int start_pixel);
};

#endif
