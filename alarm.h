#pragma once

#define ALM_THREAT_NONE     0x0
#define ALM_THREAT_FLOOD    0x1
#define ALM_THREAT_MOTION   0x2

#define ALM_LEVEL_NONE      0x0
#define ALM_LEVEL_CAUTION   0x1
#define ALM_LEVEL_IMMINENT  0x2

class Alarm {
public:

    static inline void init() {
        m_threat = ALM_THREAT_NONE;
        m_threat_level = ALM_LEVEL_NONE
    }

    static void query() {

    }

    static inline uint8_t getThreat() {
        return m_threat;
    }

    static inline uint8_t getThreatLevel() {
        return m_threat_level;
    }

private:
    static uint8_t m_threat;
    static uint8_t m_threat_level;
}
