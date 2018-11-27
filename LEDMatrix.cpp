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

void LEDMatrix::selectRow(uint8_t row)
{
    (row & 0x01) ? A->setHigh() : A->setLow();
    (row & 0x02) ? B->setHigh() : B->setLow();
    (row & 0x04) ? C->setHigh() : C->setLow();
    (row & 0x08) ? D->setHigh() : D->setLow();
    (row & 0x10) ? E->setHigh() : E->setLow();
}

void LEDMatrix::clearPixel(int row, int column)
{
    writeBuffer[row][0] &= ~(1 << column);
    writeBuffer[row][1] &= ~(1 << column);
    writeBuffer[row][2] &= ~(1 << column);
}

void LEDMatrix::setPixel(int row, int col, Colors color)
{
    if(color & 0x01) {
        writeBuffer[row][0] |= (1 << col);  //Red
    }
    if(color & 0x02) {
        writeBuffer[row][1] |= (1 << col);  //Green
    }
    if(color & 0x04) {
        writeBuffer[row][2] |= (1 << col);  //Blue
    }
}

void LEDMatrix::setRowData(uint8_t row, Colors color, uint64_t data)
{
    char str[20];
    sprintf(str, "%x",data);
    printf("Size of DATA: %u\n", sizeof(data));
    printf("Setting %s on row %u\n",str, row);
    if(color & 1) {
        printf("Setting Red Color %x on row %d\n",data, row);
        writeBuffer[row][0] = data;  //Red
    }
    if(color & 2) {
        printf("Setting Green Color %x on row %u\n",data, row);
        writeBuffer[row][1] = data;  //Green
    }
    if(color & 4) {
        printf("Setting Blue Color %x on row %u\n",data, row);
        writeBuffer[row][2] = data;  //Blue
    }
}

void LEDMatrix::setRowDataRaw(uint8_t row, ColorPlanes plane, uint64_t data)
{
    writeBuffer[row][plane] = data;
}

void LEDMatrix::clearFrameBuffers()
{
    memset(writeBuffer, 0, sizeof(writeBuffer));
    memset(readBuffer, 0, sizeof(readBuffer));
}

void LEDMatrix::fillFrameBuffer(uint64_t data, Colors color)
{
    for(uint8_t i = 0; i < 63; i++) {
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
    for(uint8_t i = 0; i < 32; i++) {
        disableDisplay();
        disableLatch();
        selectRow(i); //will select i and i + 32 rows at same time

        for(int8_t j = 63; j >= 0; j--) {
            ((readBuffer[i][0] >> j) & 1) ? r1->setHigh() : r1->setLow(); //shift in r1 data with msb getting shifted in first
            ((readBuffer[i][1] >> j) & 1) ? g1->setHigh() : g1->setLow(); //g1 data
            ((readBuffer[i][2] >> j) & 1) ? b1->setHigh() : b1->setLow(); //b1 data

            ((readBuffer[i + 32][0] >> j) & 1) ? r2->setHigh() : r2->setLow(); //r2
            ((readBuffer[i + 32][1] >> j) & 1) ? g2->setHigh() : g2->setLow(); //g2
            ((readBuffer[i + 32][2] >> j) & 1) ? b2->setHigh() : b2->setLow(); //b2
            clk->setHigh();  clk->setLow();//shift in all 3 color bits at once for top half/bottom half regs
        }
        //at this point, all 3 shift registers should be filled with corresponding row data in frameBuffer
        enableLatch(); //push shift register contents down to output registers
        enableDisplay();
    }
}
