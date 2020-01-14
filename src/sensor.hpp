#pragma once

#include <stdint.h>

void initSensors();

void queryMotionSensor(bool& isThreat);

void queryFloodSensor(bool& isThreat, bool& isImminent);