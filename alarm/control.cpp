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
 *   This is the user control. It's responsible for handling user
 *   control and button presses.
 */

#include <stdint.h>

#include "control.hpp"

#include "settings.hpp"
#include "system.hpp"
#include "pin.hpp"

bool     _ctrl_pressed;
uint64_t _ctrl_last_press;

void init_control() {
    _ctrl_pressed = false;
    _ctrl_last_press = 0;
};

uint8_t query_control() {
    const bool pressed = !System::read_pin(PIN_ARM_CTRL);
    if (!_ctrl_pressed && pressed) {
        _ctrl_pressed = true;
        _ctrl_last_press = System::get_time();
    } else if (_ctrl_pressed && !pressed)
        _ctrl_pressed = false;

    if (_ctrl_pressed) {
        const uint64_t time_since = System::get_time() - _ctrl_last_press;
        if (time_since > SETTINGS_ARM_TIME_THRESH)
            return (uint8_t) ((time_since - SETTINGS_ARM_TIME_THRESH) / SETTINGS_ARM_TICK_TIME) + 1;
    }
    
    return 0;
};

void reset_control() {
    _ctrl_pressed = false;
}
