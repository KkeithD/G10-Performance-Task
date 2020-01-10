#pragma once

#include <stdint.h>
#include <arduino.h>

class __Board {
public:
    void init();

    inline int readPin(uint8_t pin) {
        return digitalRead(pin);
    };

    inline int readAnalogPin(uint8_t pin) {
        return digitalRead(pin);
    };
    
    inline void writePin(uint8_t pin, uint8_t data) {
        digitalWrite(pin, data);
    };
};

extern __Board Board;
