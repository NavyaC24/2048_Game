/*
 * LEDMatrix.hpp
 *
 *  Created on: November 11, 2018
 *      Author: Vishal
 */

#ifndef LEDMATRIX_HPP_
#define LEDMATRIX_HPP_

#include "gpio.hpp"
#include "singleton_template.hpp"
#include "stdio.h"
#include "utilities.h"

typedef struct {
    LPC1758_GPIO_Type A;
    LPC1758_GPIO_Type B;
    LPC1758_GPIO_Type C;
    LPC1758_GPIO_Type D;
    LPC1758_GPIO_Type E;

    LPC1758_GPIO_Type latch;
    LPC1758_GPIO_Type oe;
    LPC1758_GPIO_Type clk;

    LPC1758_GPIO_Type r1;
    LPC1758_GPIO_Type g1;
    LPC1758_GPIO_Type b1;
    LPC1758_GPIO_Type r2;
    LPC1758_GPIO_Type g2;
    LPC1758_GPIO_Type b2;
}LEDMatrixDisplayPincon;

enum Color { //RGB (000 => Off)
    Off,
    Blue,
    Green,
    Cyan,
    Red,
    Pink,
    Lime,
    White
};

enum ColorPlane {
    RedPlane,
    GreenPlane,
    BluePlane
};

class LEDMatrix : public SingletonTemplate<LEDMatrix> {
    public:
        friend class SingletonTemplate<LEDMatrix>;

        GPIO *A, *B, *C, *D, *E, *latch, *oe, *clk, *r1, *g1, *b1, *r2, *g2, *b2;
        uint64_t writeBuffer[64][3]; //Use this buffer for writing data into it
        uint64_t readBuffer[64][3];  //Use this buffer to read data from it and dump onto display

    public:
        void init(LEDMatrixDisplayPincon &);
        void enableDisplay();
        void disableDisplay();
        void enableLatch();
        void disableLatch();
        void clearFrameBuffers();
        void selectRow(int row);
        void clearPixel(int row, int col);
        void setPixel(int row, int col, Color color);
        void setRowData(int row, Color color, uint64_t = 0xFFFFFFFFFFFFFFFF);
        void setRowDataRaw(int row, ColorPlane plane, uint64_t data);
        void fillFrameBuffer(uint64_t data, Color color);
        void updateReadBuffer();
        void updateDisplay();
};

#endif /* LEDMATRIX_HPP_ */
