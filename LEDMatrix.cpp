/*
 * LEDMatrix.cpp
 *
 *  Created on: November 11, 2018
 *      Author: Vishal
 */

#include "io.hpp"
#include "string.h"
#include <stdint.h>
#include "LEDMatrix.hpp"
#include "inttypes.h"


void LEDMatrix:: init(LEDMatrixDisplayPincon &pincon)
{
    //Address lines
    A = new GPIO(pincon.A);
    B = new GPIO(pincon.B);
    C = new GPIO(pincon.C);
    D = new GPIO(pincon.D);
    E = new GPIO(pincon.E);

    //Control Signals
    latch = new GPIO(pincon.latch);
    oe = new GPIO(pincon.oe);
    clk = new GPIO(pincon.clk);

    //Data lines
    r1 = new GPIO(pincon.r1);
    g1 = new GPIO(pincon.g1);
    b1 = new GPIO(pincon.b1);
    r2 = new GPIO(pincon.r2);
    g2 = new GPIO(pincon.g2);
    b2 = new GPIO(pincon.b2);

    //Set all the pins as Output
    A->setAsOutput(); B->setAsOutput(); C->setAsOutput();
    D->setAsOutput(); E->setAsOutput();
    latch->setAsOutput(); oe->setAsOutput(); clk->setAsOutput();
    r1->setAsOutput(); g1->setAsOutput(); b1->setAsOutput();
    r2->setAsOutput(); g2->setAsOutput(); b2->setAsOutput();

    //set default states
    A->setLow(); B->setLow(); C->setLow();
    D->setLow(); E->setLow();
    disableLatch(); disableDisplay();
    clk->setLow();
    r1->setLow(); g1->setLow(); b1->setLow();
    r2->setLow(); g2->setLow(); b2->setLow();

    clearFrameBuffers();
}

void LEDMatrix::enableDisplay()
{
    oe->setLow();
}

void LEDMatrix::disableDisplay()
{
    oe->setHigh();
}

void LEDMatrix::enableLatch()
{
    latch->setHigh();
}

void LEDMatrix::disableLatch()
{
    latch->setLow();
}

void LEDMatrix::selectRow(int row)
{
    (row & 0x01) ? A->setHigh() : A->setLow();
    (row & 0x02) ? B->setHigh() : B->setLow();
    (row & 0x04) ? C->setHigh() : C->setLow();
    (row & 0x08) ? D->setHigh() : D->setLow();
    (row & 0x10) ? E->setHigh() : E->setLow();
}

void LEDMatrix::clearPixel(int row, int column)
{
    uint64_t pixel = ~((uint64_t)1 << column);
    writeBuffer[row][RedPlane]   &= pixel;
    writeBuffer[row][GreenPlane] &= pixel;
    writeBuffer[row][BluePlane]  &= pixel;
}

void LEDMatrix::setPixel(int row, int col, Color color)
{
    uint64_t pixel = ((uint64_t)1 << col);
    if(color & 0x01) {
        writeBuffer[row][BluePlane]  |= pixel;
    }
    if(color & 0x02) {
        writeBuffer[row][GreenPlane] |= pixel;
    }
    if(color & 0x04) {
        writeBuffer[row][RedPlane]   |= pixel;
    }
}

void LEDMatrix::setRowData(int row, Color color, uint64_t data)
{
    if(color & 0x01) {
        writeBuffer[row][BluePlane]  = data;
    }
    if(color & 0x02) {
        writeBuffer[row][GreenPlane] = data;
    }
    if(color & 0x04) {
        writeBuffer[row][RedPlane]   = data;
    }
}

void LEDMatrix::setRowDataRaw(int row, ColorPlane plane, uint64_t data)
{
    writeBuffer[row][plane] = data;
}

void LEDMatrix::clearFrameBuffers()
{
    memset(writeBuffer, 0, sizeof(writeBuffer));
    memset(readBuffer, 0, sizeof(readBuffer));
}

void LEDMatrix::fillFrameBuffer(uint64_t data, Color color)
{
    for(int i = 0; i < 64; i++) {
        setRowData(i, color, data);
    }
}

void LEDMatrix::updateReadBuffer()
{
    //Copies data from write buffer to read buffer; Must be called in updateDisplay()
    //Having two buffers will avoid continuous write operations on buffer while it is being read, marginally.
    memcpy(readBuffer, writeBuffer, sizeof(readBuffer));
}

void LEDMatrix::updateDisplay()
{
    updateReadBuffer();
    for(int i = 0; i < 32; i++) {
        disableDisplay();
        disableLatch();
        selectRow(i); //will select i and i + 32 rows at same time

        for(int j = 63; j >= 0; j--) {
            ((readBuffer[i][RedPlane]   >> j) & 1) ? r1->setHigh() : r1->setLow(); //shift in r1 data with msb getting shifted in first
            ((readBuffer[i][GreenPlane] >> j) & 1) ? g1->setHigh() : g1->setLow(); //g1 data
            ((readBuffer[i][BluePlane]  >> j) & 1) ? b1->setHigh() : b1->setLow(); //b1 data

            ((readBuffer[i + 32][RedPlane]   >> j) & 1) ? r2->setHigh() : r2->setLow(); //r2
            ((readBuffer[i + 32][GreenPlane] >> j) & 1) ? g2->setHigh() : g2->setLow(); //g2
            ((readBuffer[i + 32][BluePlane]  >> j) & 1) ? b2->setHigh() : b2->setLow(); //b2
            clk->setHigh();  clk->setLow();//shift in all 3 color bits at once for top half/bottom half regs
            enableLatch(); disableLatch();
        }
        //at this point, all 3 shift registers should be filled with corresponding row data in frameBuffer
        enableLatch(); //push shift register contents down to output registers
        enableDisplay();
        delay_us(80);
    }
    disableDisplay();
}
