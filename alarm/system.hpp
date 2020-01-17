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
 *   This is the core system logic. All major program processes
 *   are defined here.
 */

#pragma once

#include <arduino.h>
#include <stdint.h>

#include "graphics.hpp"

#define SYS_STATE_INIT            0x0
#define SYS_STATE_NEUTRAL         0x1
#define SYS_STATE_ARMED           0x2
#define SYS_STATE_DISARMED        0x3

#define SYS_THREAT_NONE           0x0
#define SYS_THREAT_MOTION         0x1
#define SYS_THREAT_FLOOD          0x2

namespace System {
    // Gets time since system started in ms
    inline uint64_t get_time() {
        return millis();
    }

    // Reads digital data from pin
    inline int read_pin(uint8_t pin) {
        return digitalRead(pin);
    };

    // Reads analog data from pin
    inline int read_analog_pin(uint8_t pin) {
        return analogRead(pin);
    };

    // Writes digital data to pin
    inline void write_pin(uint8_t pin, uint8_t data) {
        digitalWrite(pin, data);
    };

    // Initializes system
    void initialize();

    // Queries system
    void query();
};
