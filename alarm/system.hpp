#pragma once

#include <stdint.h>
#include <arduino.h>

#include "graphics.hpp"

#define SYS_STATE_INIT            0x0
#define SYS_STATE_NEUTRAL         0x1
#define SYS_STATE_ARMED           0x2
#define SYS_STATE_DISARMED        0x3

#define SYS_THREAT_NONE           0x0
#define SYS_THREAT_MOTION         0x1
#define SYS_THREAT_FLOOD          0x2

namespace System {
    inline uint64_t get_time() {
        return millis();
    }

    inline int read_pin(uint8_t pin) {
        return digitalRead(pin);
    };

    inline int read_analog_pin(uint8_t pin) {
        return analogRead(pin);
    };

    inline void write_pin(uint8_t pin, uint8_t data) {
        digitalWrite(pin, data);
    };

    void initialize();

    void query();
};
