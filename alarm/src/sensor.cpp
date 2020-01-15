#pragma once

#include <stdlib.h>

#include "settings.hpp"
#include "sensor.hpp"
#include "system.hpp"
#include "pin.hpp"

double _last_light_lvl;
double _light_lvl;

void initializeSensors() {
    _last_light_lvl = 0;
    _light_lvl = 0;
};

void calibrateSensors() {
    getMotionThreat();
    getFloodThreat();
};

bool getMotionThreat() {
    _last_light_lvl = _light_lvl;
    _light_lvl = (double) System::readAnalogPin(PIN_MOTION_SENS);
    return abs(_light_lvl-_last_light_lvl) > SETTINGS_MOTION_THRESH;
};

bool getFloodThreat() {

};
