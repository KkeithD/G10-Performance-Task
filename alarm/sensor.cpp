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
 *   This is the sensor control. It's responsible for processing information
 *   from the flood and motion sensors, and relaying that information to the
 *   rest of the program.
 */

#pragma once

#include <stdlib.h>

#include "sensor.hpp"

#include "settings.hpp"
#include "system.hpp"
#include "pin.hpp"

double _sen_last_light_lvl;
double _sen_light_lvl;

void init_sensors() {
    _sen_last_light_lvl = 0;
    _sen_light_lvl = 0;
};

void calib_sensors() {
    get_motion_threat();
    get_flood_threat();
};

bool get_motion_threat() {
    _sen_last_light_lvl = _sen_last_light_lvl*(1-SETTINGS_MOTION_SMOOTHING) + _sen_light_lvl*SETTINGS_MOTION_SMOOTHING;
    _sen_light_lvl = (double) System::read_analog_pin(PIN_MOTION_SENS);
    return (abs(_sen_light_lvl-_sen_last_light_lvl) > SETTINGS_MOTION_THRESH);
};

bool get_flood_threat() {

};
