#include "alarm.h"

void __Alarm::init() {
    m_threat = ALM_THREAT_NONE;
    m_threat_level = ALM_LEVEL_NONE
};

void __Alarm::query() {
    if (!Control::isArmed())
        return;
};

inline uint8_t __Alarm::getThreat() {
    return m_threat;
};

inline uint8_t __Alarm::getThreatLevel() {
    return m_threat_level;
};

__Alarm Alarm;