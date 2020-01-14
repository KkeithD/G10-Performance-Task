#pragma once

#include <stdint.h>
#include <arduino.h>

#include "graphics.dat"

#define SYS_STATE_INIT            0x0
#define SYS_STATE_NEUTRAL         0x1
#define SYS_STATE_THREAT          0x2

#define SYS_CTRL_ARMED            0x1
#define SYS_CTRL_DISARMED         0x0

#define SYS_THREAT_NONE           0x0
#define SYS_THREAT_MOTION         0x1
#define SYS_THREAT_FLOOD          0x2

#define SYS_THREAT_LEVEL_NONE     0x0
#define SYS_THREAT_LEVEL_CAUTION  0x1
#define SYS_THREAT_LEVEL_IMMINENT 0x2

namespace System {
    inline int readBoardPin(uint8_t pin) {
        return digitalRead(pin);
    };

    inline int readAnalogBoardPin(uint8_t pin) {
        return analogRead(pin);
    };

    inline void writeBoardPin(uint8_t pin, uint8_t data) {
        digitalWrite(pin, data);
    };

    void initialize();

    void query();

    void setSystemState(uint8_t state);

    uint8_t getSystemState();

    void setThreatState(uint8_t threat_state);

    uint8_t getThreatState();
    
    void setThreatLevel(uint8_t threat_level);

    uint8_t getThreatLevel();

    inline void writeConsole(char* data) {
        Serial.print(data);
    };
    
    inline void writeConsole(std::string data) {
        Serial.print(data.data());
    };    

    char* getConsoleData();

    inline bool hasConsoleData() {
        return Serial.available();
    };

    inline void flushConsole(bool full_flush) {
        if (full_flush)
            writeConsole(SYS_CONSOLE_FLUSH);
        } else 
            writeGraphic(SYS_GRAPHIC_TYPE_EMPTY);
    };

    void writeGraphic(uint8_t graphic_type);
};



