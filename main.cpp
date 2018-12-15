/*
 * main.cpp
 *
 *  Created on: Nov 26, 2018
 *      Author: Team 2048
 *
 *     This file is a part of project developed by Team 2048 as part of the curriculum
 *     of the course CMPE 244 of SJSU in Fall 2018 semester.
 *
 *     Usage of this file and/or the project is governed by the Apache 2.0 License agreement.
 *
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
#include "JoystickApp.hpp"

void gameLogicTask(void *p);
void displayTask(void *p);

LEDMatrixDisplayPincon displayPincon;
DisplayApp displayApp;
JoystickApp js(k0_26, k1_31);
Game game(&displayApp, &js);

void displayTask(void *p)
{
    while(1) {
        displayApp.updateDisplay();
        vTaskDelay(7);
    }
}

void gameLogicTask(void *p)
{
    game.generateNewTile();
    game.generateNewTile();
    while(1) {
        game.run();
        vTaskDelay(150);
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
    xTaskCreate(displayTask, "Display", STACK_SIZE, 0, PRIORITY_HIGH, NULL);
    xTaskCreate(gameLogicTask, "Game", STACK_SIZE, 0, PRIORITY_MEDIUM, NULL);

    //scheduler_add_task(new terminalTask(PRIORITY_HIGH));
    //scheduler_start(); ///< This shouldn't return

    vTaskStartScheduler();
    return -1;
}
