#pragma once

#include <stdint.h>

void initSensors();

void queryMotionThreat(bool& isThreat);

void queryFloodThreat(bool& isThreat, bool& isImminent);
