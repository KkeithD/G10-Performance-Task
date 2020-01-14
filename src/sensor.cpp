#pragma once

#include <stdlib.h>

#include "sensor.hpp"
#include "settings.hpp"
#include "pin.hpp"
#include "system.hpp"

double _last_light_lvl;
double _light_lvl;

double 


void initSensors() {
    _last_light_lvl = 0;
    _light_lvl = 0;
};

bool getMotionThreat() {
    _last_light_lvl = _light_lvl;
    _light_lvl = (double) readAnalogBoardPin(PIN_MOTION_SENS);
    
    return abs(_light_lvl-_last_light_lvl) > SETTINGS_MOTION_THRESH;
};

bool getFloodThreat() {

};
