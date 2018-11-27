/*
 * main.cpp
 *
 *  Created on: Nov 26, 2018
 *      Author: Vishal
 */

/*
 *     SocialLedge.com - Copyright (C) 2013
 *
 *     This file is part of free software framework for embedded processors.
 *     You can use it and/or distribute it as long as this copyright header
 *     remains unmodified.  The code is free for personal use and requires
 *     permission to use in a commercial product.
 *
 *      THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 *      OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 *      MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 *      I SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 *      CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *     You can reach the author of this software at :
 *          p r e e t . w i k i @ g m a i l . c o m
 */

/**
 * @file
 * @brief This is the application entry point.
 *          FreeRTOS and stdio printf is pre-configured to use uart0_min.h before main() enters.
 *          @see L0_LowLevel/lpc_sys.h if you wish to override printf/scanf functions.
 *
 */
#include "LEDMatrix.hpp"
#include "tasks.hpp"
#include "examples/examples.hpp"
#include "io.hpp"
#include <stdio.h>
#include "LPC17xx.h"
#include "gpio.hpp"
#include "storage.hpp"
#include "string.h"
#include "time.h"
#include "lpc_rit.h"
#include "eint.h"
#include "semphr.h"
#include "math.h"
#include "lpc_pwm.hpp"
#include "GameLogic.hpp"
#include "FreeRTOS.h"
#include "utilities.h"

LEDMatrixDisplayPincon displayPincon;
LEDMatrix display = LEDMatrix::getInstance();
GameLogic game;
uint64_t data2 = 0x0000000000000001;
uint64_t data1 = 0xFFFFFFFFFFFFFFFF;
uint64_t line1 = 0xF0F0F0F0F0F0F0F0;
uint64_t line2 = 0x0000000000000000;
uint64_t buf[64][3] = {{line2, line2, line2}, {0x8001000200040008, 0xB89D713AE275C4E8, 0x8001000200040008},
                       {0x8001000200040008, 0xC1838307060E0C18, 0x8001000200040008}, {0x8001000200040008, 0xF89FF13FE27FC4F8, 0x8001000200040008},
                       {0x8001000200040008, 0x8891112222444488, 0x8001000200040008}, {0x8001000200040008, 0xF9DFF3BFE77FCEF8, 0x8001000200040008},
                       {0xFFFFFFFFFFFFFFF8, 0xFFFFFFFFFFFFFFF8, 0xFFFFFFFFFFFFFFF8}, {0x8001000200040008, 0xB89D713AE275C4E8, 0x8001000200040008},
                       {0x8001000200040008, 0xC1838307060E0C18, 0x8001000200040008}, {0x8001000200040008, 0xF89FF13FE27FC4F8, 0x8001000200040008},
                       {0x8001000200040008, 0x8891112222444488, 0x8001000200040008}, {0x8001000200040008, 0xF9DFF3BFE77FCEF8, 0x8001000200040008},
                       {0xFFFFFFFFFFFFFFF8, 0xFFFFFFFFFFFFFFF8, 0xFFFFFFFFFFFFFFF8}, {0x8001000200040008, 0xB89D713AE275C4E8, 0x8001000200040008},
                       {0x8001000200040008, 0xC1838307060E0C18, 0x8001000200040008}, {0x8001000200040008, 0xF89FF13FE27FC4F8, 0x8001000200040008},
                       {0x8001000200040008, 0x8891112222444488, 0x8001000200040008}, {0x8001000200040008, 0xF9DFF3BFE77FCEF8, 0x8001000200040008},
                       {0xFFFFFFFFFFFFFFF8, 0xFFFFFFFFFFFFFFF8, 0xFFFFFFFFFFFFFFF8}, {0x8001000200040008, 0xB89D713AE275C4E8, 0x8001000200040008},
                       {0x8001000200040008, 0xC1838307060E0C18, 0x8001000200040008}, {0x8001000200040008, 0xF89FF13FE27FC4F8, 0x8001000200040008},
                       {0x8001000200040008, 0x8891112222444488, 0x8001000200040008}, {0x8001000200040008, 0xF9DFF3BFE77FCEF8, 0x8001000200040008},
                       {0xFFFFFFFFFFFFFFF8, 0xFFFFFFFFFFFFFFF8, 0xFFFFFFFFFFFFFFF8}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}
                    };
uint64_t buf1[64][3] = {{0xCE25CE25CE25CE24, 0x0001000100010000, 0x0001000100010000},
                       {0x2A6B2A6B2A6B2A6A, 0x0001000100010000, 0x0001000100010000}, {0x4AAF4AAF4AAF4AAE, 0x0001000100010000, 0x0001000100010000},
                       {0x8AEB8AEB8AEB8AEA, 0x0001000100010000, 0x0001000100010000}, {0xEE24EE25EE25EE24, 0x0001000100010000, 0x0001000100010000},
                       {0xFFFFFFFFFFFFFFFE, 0xFFFFFFFFFFFFFFFE, 0xFFFFFFFFFFFFFFFE}, {0xCE25CE25CE25CE24, 0x0001000100010000, 0x0001000100010000},
                       {0x2A6B2A6B2A6B2A6A, 0x0001000100010000, 0x0001000100010000}, {0x4AAF4AAF4AAF4AAE, 0x0001000100010000, 0x0001000100010000},
                       {0x8AEB8AEB8AEB8AEA, 0x0001000100010000, 0x0001000100010000}, {0xEE24EE25EE25EE24, 0x0001000100010000, 0x0001000100010000},
                       {0xFFFFFFFFFFFFFFFE, 0xFFFFFFFFFFFFFFFE, 0xFFFFFFFFFFFFFFFE}, {0xCE25CE25CE25CE24, 0x0001000100010000, 0x0001000100010000},
                       {0x2A6B2A6B2A6B2A6A, 0x0001000100010000, 0x0001000100010000}, {0x4AAF4AAF4AAF4AAE, 0x0001000100010000, 0x0001000100010000},
                       {0x8AEB8AEB8AEB8AEA, 0x0001000100010000, 0x0001000100010000}, {0xEE24EE25EE25EE24, 0x0001000100010000, 0x0001000100010000},
                       {0xFFFFFFFFFFFFFFFE, 0xFFFFFFFFFFFFFFFE, 0xFFFFFFFFFFFFFFFE}, {0xCE25CE25CE25CE24, 0x0001000100010000, 0x0001000100010000},
                       {0x2A6B2A6B2A6B2A6A, 0x0001000100010000, 0x0001000100010000}, {0x4AAF4AAF4AAF4AAE, 0x0001000100010000, 0x0001000100010000},
                       {0x8AEB8AEB8AEB8AEA, 0x0001000100010000, 0x0001000100010000}, {0xEE24EE25EE25EE24, 0x0001000100010000, 0x0001000100010000},
                       {0,0,0}, {0,0,0}, {0,0,0}, {0xFFFF000000000000, 0xFFFF000000000000, 0xFFFF000000000000},
                       {0xFFFF000000000000, 0xFFFF000000000000, 0xFFFF000000000000}, {0xFFFF000000000000, 0xFFFF000000000000, 0xFFFF000000000000},
                       {0xFFFF000000000000, 0xFFFF000000000000, 0xFFFF000000000000}, {0xFFFF000000000000, 0xFFFF000000000000, 0xFFFF000000000000}
                       };

uint64_t deepak[64][3] = {{0xFFFF000000000000, 0xFFFF000000000000, 0x0000000000000000},
        {0xFFFF000000000000, 0xFFFF000000000000, 0x0000000000000000}, {0xFFFF000000000000, 0xFFFF000000000000, 0x0000000000000000},
        {0xFFFF000000000000, 0xFFFF000000000000, 0x0000000000000000}, {0xFFFF000000000000, 0xFFFF000000000000, 0x0000000000000000}};

uint64_t xyz[] = {0xE0E0E0E0E0E0E0E0, 0x1010101010101010, 0x7070707070707070, 0x8080808080808080, 0xF0F0F0F0F0F0F0F0, 0x0000000000000000};
static void refresh()
{
    display.updateDisplay();
}

void displayLine(uint64_t (*d)[3], int row)
{
    display.disableDisplay();
    display.disableLatch();
    display.selectRow(row);
    for(int j = 63; j >= 0; j--) {
        ((d[row][RedPlane]   >> j) & 1) ? display.r1->setHigh() : display.r1->setLow();
        ((d[row][GreenPlane] >> j) & 1) ? display.g1->setHigh() : display.g1->setLow();
        ((d[row][BluePlane]  >> j) & 1) ? display.b1->setHigh() : display.b1->setLow();
        ((d[row][RedPlane]   >> j) & 0) ? display.r2->setHigh() : display.r2->setLow();
        ((d[row][GreenPlane] >> j) & 0) ? display.g2->setHigh() : display.b2->setLow();
        ((d[row][BluePlane]  >> j) & 0) ? display.b2->setHigh() : display.g2->setLow();
        display.clk->setHigh(); display.clk->setLow();
    }
    display.enableLatch();
    display.enableDisplay();
}

void displayLine1(uint64_t d, int row)
{
    display.disableDisplay();
    display.disableLatch();
    display.selectRow(row);
    for(int j = 63; j >= 0; j--) {
        ((d >> j) & 1) ? display.r1->setHigh() : display.r1->setLow();
        ((d >> j) & 0) ? display.g1->setHigh() : display.g1->setLow();
        ((d >> j) & 0) ? display.b1->setHigh() : display.b1->setLow();
        ((d >> j) & 1) ? display.r2->setHigh() : display.r2->setLow();
        ((d >> j) & 0) ? display.g2->setHigh() : display.b2->setLow();
        ((d >> j) & 0) ? display.b2->setHigh() : display.g2->setLow();
        display.clk->setHigh(); display.clk->setLow();
    }
    display.enableLatch();
    display.enableDisplay();
}

void displayTask(void *p)
{
    while(1) {
        for(int i = 0; i < 32; i++) {
           displayLine(buf1, i);
           delay_us(40);
        }
    }
}

int main(void)
{
    const uint32_t STACK_SIZE = 2048;

    //Pin Connections of LED Matrix Display
    //Address Lines
    displayPincon.A = P2_1;
    displayPincon.B = P2_2;
    displayPincon.C = P2_3;
    displayPincon.D = P2_4;
    displayPincon.E = P2_5;

    //Control Signals
    displayPincon.oe    = P1_19;
    displayPincon.latch = P0_29;
    displayPincon.clk   = P0_30;

    //Data Lines
    displayPincon.r1 = P1_30;
    displayPincon.g1 = P1_29;
    displayPincon.b1 = P1_28;
    displayPincon.r2 = P1_23;
    displayPincon.g2 = P1_22;
    displayPincon.b2 = P1_20;

    display.init(displayPincon);
    game.drawGridBorders();
    xTaskCreate(displayTask, "LEDTask", STACK_SIZE, 0, PRIORITY_HIGH, NULL);

    scheduler_add_task(new terminalTask(PRIORITY_HIGH));
    scheduler_start(); ///< This shouldn't return
    return -1;
}
