#pragma once

#include <stdint.h>
#include <arduino.h>


#include "pin.hpp"

inline void alarm_play_tone(uint32_t freq) {
    tone(PIN_BUZZER_INDC, freq);
};

void alarm_play_tone(uint32_t freq, uint64_t ms) {
    tone(PIN_BUZZER_INDC, freq);
    delay(ms);
    noTone(PIN_BUZZER_INDC);
};

inline void alarm_stop_tone() {
    noTone(PIN_BUZZER_INDC);
}
