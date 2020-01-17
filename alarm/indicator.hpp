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
 *   This is the indicator control. It's responsible for controlling the
 *   LED indicators and ensuring they represent the correct armed state.
 */

#pragma once

#define SYS_INDC_ARMED    0x1
#define SYS_INDC_DISARMED 0x0

#define SYS_INDC_ON       0x1
#define SYS_INDC_OFF      0x0

// Initializes indicator
void init_indicator();

// Set's indicator state
void set_indicator_state(bool is_on, bool is_armed);
