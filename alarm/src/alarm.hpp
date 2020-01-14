#pragma once

#include <stdint.h>

#define ALM_THREAT_NONE     0x0
#define ALM_THREAT_FLOOD    0x1
#define ALM_THREAT_MOTION   0x2

#define ALM_LEVEL_NONE      0x0
#define ALM_LEVEL_CAUTION   0x1
#define ALM_LEVEL_IMMINENT  0x2

#define ALM_ARMED           true
#define ARM_DISARMED        false

void initAlarm();

void playAlarmTone(uint32_t freq, uint32_t ms);
