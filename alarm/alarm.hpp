/**
 * 
 *     /$$$$$$            /$$    /$$$$$$        /$$$$$$$  /$$$$$$$$ /$$$$$$$$
 *    /$$__  $$         /$$$$   /$$$_  $$      | $$__  $$| $$_____/|__  $$__/
 *   | $$  \__/        |_  $$  | $$$$\ $$      | $$  \ $$| $$         | $$   
 *   | $$ /$$$$ /$$$$$$  | $$  | $$ $$ $$      | $$$$$$$/| $$$$$      | $$   
 *   | $$|_  $$|______/  | $$  | $$\ $$$$      | $$____/ | $$__/      | $$   
 *   | $$  \ $$          | $$  | $$ \ $$$      | $$      | $$         | $$   
 *   |  $$$$$$/         /$$$$$$|  $$$$$$/      | $$      | $$         | $$   
 *   \______/         |______/ \______/       |__/      |__/         |__/   
 *   
 *   By ~ Keith Davies.
 *   
 *   This is the alarm control. It's responsible for controlling alarm
 *   functionality. It handles actions like playing tones, stopping 
 *   tones,
 */

#pragma once

#include <arduino.h>
#include <stdint.h>

#include "pin.hpp"

// Plays an alarm tone at a specified frequency
inline void alarm_play_tone(uint32_t freq) {
    tone(PIN_BUZZER_INDC, freq);
};

// Plays an alarm tone at a specified frequency for x milliseconds.
void alarm_play_tone(uint32_t freq, uint64_t ms) {
    tone(PIN_BUZZER_INDC, freq);
    delay(ms);
    noTone(PIN_BUZZER_INDC);
};

// Stops any running alarm tone
inline void alarm_stop_tone() {
    noTone(PIN_BUZZER_INDC);
}
