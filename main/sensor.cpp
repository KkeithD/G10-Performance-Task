#pragma once

#include <stdlib.h>

#include "sensor.hpp"
#include "settings.hpp"
#include "pin.hpp"
#include "board.hpp"

double _raw_light_bounds;
double _last_light_lvl;
double _light_lvl;


void initSensors() {
    _raw_light_bounds = 0;
    _last_light_lvl = 0;
    _light_lvl = 0;
};

void queryMotionThreat(bool& isThreat) {
    _last_light_lvl = _light_lvl;
    _light_lvl = readAnalogBoardPin(PIN_MOTION_SENS);
    
    //Serial.println(abs(_light_lvl-_last_light_lvl));
    isThreat = abs(_light_lvl-_last_light_lvl) > SETTINGS_MOTION_THRESH;
};

void queryFloodThreat(bool& isThreat, bool& isImminent) {

};
