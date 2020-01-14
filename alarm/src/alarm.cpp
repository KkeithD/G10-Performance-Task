#include "alarm.hpp"

#include <arduino.h>

void playAlarmTone(uint32_t freq, uint64_t ms) {
    tone(PIN_BUZZER_INDC, freq);
};

void noAlarmTone() {
    noTone(PIN_BUZZER_INDC);
}
