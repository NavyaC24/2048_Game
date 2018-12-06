/*
 * main.cpp
 *
 *  Created on: Nov 26, 2018
 *      Author: Team 2048
 */

/*
 *     This file is a part of project developed by Team 2048 as part of the curriculum
 *     of the course CMPE 244 of SJSU in Fall 2018 semester.
 *
 *     Usage of this file and/or the project is governed by the Apache 2.0 License agreement,
 *     as mentioned in the LICENSE file.
 *     /

/**
 * @file
 * @brief This is the application entry point.
 *          FreeRTOS and stdio printf is pre-configured to use uart0_min.h before main() enters.
 *          @see L0_LowLevel/lpc_sys.h if you wish to override printf/scanf functions.
 *
 */

#include "tasks.hpp"
#include "io.hpp"
#include <stdio.h>
#include "LPC17xx.h"
#include "gpio.hpp"
#include "GameLogic.hpp"
#include "FreeRTOS.h"
#include "adc0.h"
#include "string.h"

LEDMatrixDisplayPincon displayPincon;
DisplayApp displayApp;
GameLogic game(&displayApp);
uint16_t xvalue;
uint16_t yvalue;

void displayTask(void *p)
{
    while(1) {
        printf("Changing grid\n");
        int game_grid2[4][4] = {{0, 2, 0, 0},
                                {0, 0, 2, 0},
                                {0, 0, 0, 0},
                                {0, 0, 0, 0}};
        memcpy(game.grid, game_grid2, sizeof(game_grid2));
        game.updateGrid();
        vTaskDelay(2000);
        printf("Changing grid\n");
        int game_grid3[4][4] = {{2, 0, 0, 0},
                                {0, 2, 0, 2},
                                {0, 0, 0, 0},
                                {0, 0, 0, 0}};
        memcpy(game.grid, game_grid3, sizeof(game_grid3));
        game.updateGrid();
        vTaskDelay(2000);
        printf("Changing grid\n");
        int game_grid4[4][4] = {{2, 0, 0, 0},
                                {4, 0, 0, 0},
                                {0, 0, 0, 4},
                                {0, 0, 0, 0}};
        memcpy(game.grid, game_grid4, sizeof(game_grid4));
        game.updateGrid();
        vTaskDelay(2000);
    }
}

void displayTask2(void *p)
{
    while(1) {
        displayApp.updateDisplay();
        vTaskDelay(6);
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

    displayApp.initDisplay(displayPincon);
//    xTaskCreate(displayTask, "LEDTask", STACK_SIZE, 0, PRIORITY_HIGH, NULL);
    xTaskCreate(displayTask2, "LEDTask2", STACK_SIZE, 0, PRIORITY_HIGH, NULL);

    //scheduler_add_task(new terminalTask(PRIORITY_HIGH));
    //scheduler_start(); ///< This shouldn't return

    vTaskStartScheduler();
    return -1;
}
