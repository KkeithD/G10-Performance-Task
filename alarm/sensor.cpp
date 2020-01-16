#pragma once

#include <stdlib.h>

#include "sensor.hpp"

#include "pin.hpp"
#include "system.hpp"
#include "settings.hpp"

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
    _sen_last_light_lvl = _sen_light_lvl;
    _sen_light_lvl = (double) System::read_analog_pin(PIN_MOTION_SENS);
    return (abs(_sen_light_lvl-_sen_last_light_lvl) > SETTINGS_MOTION_THRESH);
};

bool get_flood_threat() {

};
