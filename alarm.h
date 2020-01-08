#pragma once

#include "control.h"

#define ALM_THREAT_NONE     0x0
#define ALM_THREAT_FLOOD    0x1
#define ALM_THREAT_MOTION   0x2

#define ALM_LEVEL_NONE      0x0
#define ALM_LEVEL_CAUTION   0x1
#define ALM_LEVEL_IMMINENT  0x2

#define ALM_ARMED           true
#define ARM_DISARMED        false

class __Alarm {
public:

    void init();

    void query();

    inline uint8_t getThreat();

    inline uint8_t getThreatLevel();

private:
    uint8_t m_threat;
    uint8_t m_threat_level;
};

extern __Alarm Alarm;