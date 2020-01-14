#include <arduino.h>
#include <string.h>
#include <stdint.h>

#include "../lib/sha256/sha256.hpp"

#include "graphics.hpp"

#include "pass_sha.hpp"
#include "system.hpp"
#include "alarm.hpp"
#include "sensor.hpp"
#include "pin.hpp"

#define INITIALIZE_PIN(name) pinMode(PIN_ ## name, PIN_MODE_ ## name);

uint8_t*      _sys_pass;
Sha256*       _sys_sha256_inst;

uint8_t       _sys_state;
uint8_t       _sys_threat_state;
uint8_t       _sys_threat_level;

namespace System {
    void initialize() {
        INITIALIZE_PIN(      ARM_CTRL )
        INITIALIZE_PIN(    ARMED_INDC )
        INITIALIZE_PIN( DISARMED_INDC )
        INITIALIZE_PIN(   BUZZER_INDC )
        INITIALIZE_PIN(   MOTION_SENS )
        INITIALIZE_PIN(    FLOOD_SENS )

        _sys_state = SYS_STATE_INIT;
        _sys_threat_state = SYS_CTRL_DISARMED;
        _sys_threat_level = SYS_THREAT_LEVEL_NONE;

        _sys_pass = getSystemPass();
        _sys_sha256_inst = new Sha256();

        flushConsole(true);
        writeConsole(SYS_GRAPHIC_CALIBRATION);

        uint64_t init_time = getTime();
        while (true) {
            while (!hasConsoleData()) {
                getMotionThreat(); // Calibrate sensors
                getFloodThreat();
            }
        }
        init_time = getTime() - init_time;

        flushConsole(true);
        writeGraphic(SYS_GRAPHIC_TYPE_INIT);
        
        if (init_time < 3000) {
            for (int i=0; i<3; i++) {
                uint64_t time_now = getTime();
                playAlarmTone(5000, 0);
                while (getTime() - time_now)

        }

        for (int i=0; i<3; i++) {
            writeConsole("DONE\n");
        }
    };

    void query() {

    };

    void setSystemState(uint8_t state) {
        _sys_state = state;
    };

    uint8_t getSystemState() {
        return _sys_state;
    };

    void setThreatState(uint8_t threat_state) {
        _sys_threat_state = threat_state;
    };

    uint8_t getThreatState() {
        return _sys_threat_state;
    };

    void setThreatLevel(uint8_t threat_level) {
        _sys_threat_level = threat_level;
    };

    uint8_t getThreatLevel() {
        return _sys_threat_level;
    };

    void writeGraphic(uint8_t graphic_type) {
        writeConsole(SYS_CONSOLE_FLUSH);
        writeConsole(SYS_GRAPHIC_BASE_TOP);
            switch(graphic_type) {
                case    SYS_GRAPHIC_TYPE_EMPTY: writeConsole(SYS_GRAPHIC_TEXT_NONE); break;
                case     SYS_GRAPHIC_TYPE_INIT: writeConsole(SYS_GRAPHIC_TEXT_INIT); break;
                case  SYS_GRAPHIC_TYPE_WELCOME: writeConsole(SYS_GRAPHIC_TEXT_WELCOME); break;
                case    SYS_GRAPHIC_TYPE_ARMED: writeConsole(SYS_GRAPHIC_TEXT_ARMED); break;
                case SYS_GRAPHIC_TYPE_DISARMED: writeConsole(SYS_GRAPHIC_TEXT_DISARMED); break;
                case SYS_GRAPHIC_TYPE_INTRUDER: writeConsole(SYS_GRAPHIC_TEXT_INIT); break;
                case    SYS_GRAPHIC_TYPE_FLOOD: writeConsole(SYS_GRAPHIC_TEXT_FLOOD); break;
            }
        writeConsole(SYS_GRAPHIC_BASE_BOTTOM);
    };

    char* getConsoleData() {
        char* data = new char[0]; //TODO: use low level funcs instead of standard lib

        int len = 0;
        while (hasConsoleData()) {
            const char in_char = (char) Serial.read();

            len++;
            Serial.println(in_char);
            char* new_data = new char[len];
            
            strcpy(new_data, data);
            new_data[len-1] = in_char;
            
            delete data;
            data = new_data;
        }
        Serial.println(len);
        return data;
    };
};