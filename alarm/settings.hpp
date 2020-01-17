/**
 * 
 *     /$$$$$$            /$$    /$$$$$$        /$$$$$$$  /$$$$$$$$ /$$$$$$$$
 *    /$$__  $$         /$$$$   /$$$_  $$      | $$__  $$| $$_____/|__  $$__/
 *   | $$  \__/        |_  $$  | $$$$\ $$      | $$  \ $$| $$         | $$   
 *   | $$ /$$$$ /$$$$$$  | $$  | $$ $$ $$      | $$$$$$$/| $$$$$      | $$   
 *   | $$|_  $$|______/  | $$  | $$\ $$$$      | $$____/ | $$__/      | $$   
 *   | $$  \ $$          | $$  | $$ \ $$$      | $$      | $$         | $$   
 *   |  $$$$$$/         /$$$$$$|  $$$$$$/      | $$      | $$         | $$   
 *   \______/         |______/ \______/       |__/      |__/         |__/   
 *   
 *   By ~ Keith Davies.
 *   
 *   This is where the program settings are defined. They represent variable
 *   processes within the program that required tuning in order to function
 *   effectively.
 */

#pragma once

#define SETTINGS_SERIAL_BAUD_RATE 500000

#define SETTINGS_MOTION_THRESH  1.5

#define SETTINGS_MOTION_SMOOTHING 0.2

#define SETTINGS_ARMED_TICK_COUNT 5

#define SETTINGS_ARMED_TICK_TIME 320

#define SETTINGS_ARM_TICK_COUNT 4

#define SETTINGS_ARM_TIME_THRESH 500

#define SETTINGS_ARM_TICK_TIME 500

#define SETTINGS_INIT_STEP_TIME 325 // ms

#define SETTINGS_INIT_NUM_STEPS 3

#define SETTINGS_MAX_MSG_LEN    32
