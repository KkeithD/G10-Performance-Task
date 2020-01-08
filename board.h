#pragma once

#include <arduino.h>

#define INIT_PIN(name) pinMode(PIN_ ## name, PIN_MODE_ ## name);

class __Board {
public:
    void init() {
        INIT_PIN(     ARM_CTRL)
        INIT_PIN(   ARMED_INDC)
        INIT_PIN(DISARMED_INDC)
        INIT_PIN(  BUZZER_INDC)
        INIT_PIN(  MOTION_SENS)
        INIT_PIN(   FLOOD_SENS
    }

    inline int readPin(uint8_t pin) {
        return digitalRead(pin);
    }

    inline void readPin(uint8_t pin) {
        digitalWrite(pin);
    }
}

extern __Board Board;

#undef INIT_PIN