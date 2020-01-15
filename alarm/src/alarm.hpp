#pragma once

#include <stdint.h>
#include "pin.hpp"
#include <arduino.h>

#define ALM_THREAT_NONE     0x0
#define ALM_THREAT_FLOOD    0x1
#define ALM_THREAT_MOTION   0x2

#define ALM_LEVEL_NONE      0x0
#define ALM_LEVEL_CAUTION   0x1
#define ALM_LEVEL_IMMINENT  0x2

#define ALM_ARMED           true
#define ARM_DISARMED        false

inline void playTone(uint32_t freq) {
    tone(PIN_BUZZER_INDC, freq);
};

void playTone(uint32_t freq, uint64_t ms) {
    tone(PIN_BUZZER_INDC, freq);
    delay(ms);
    noTone(PIN_BUZZER_INDC);
};

inline void stopTone() {
    noTone(PIN_BUZZER_INDC);
}

