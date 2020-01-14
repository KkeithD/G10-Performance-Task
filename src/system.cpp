#include <lib/sha256/sha256.hpp>
#include <arduino.h>
#include <string.h>

#include "graphics.dat"

#include "pass_sha.hpp"
#include "system.hpp"
#include "sensor.hpp"
#include "pin.hpp"

#define INITIALIZE_PIN(name) pinMode(PIN_ ## name, PIN_MODE_ ## name);

const uint8_t _sys_pass[SHA256_BLOCK_SIZE];
Sha256        _sys_sha256_inst;

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

        while (true) {
            while (!hasConsoleData()) {
                queryMotionSensor(); // Calibrate sensors
                queryFloodSensor();
            }
           
            if (strcmp('start', getConsoleData() == 0)
                break;
        }

        flushConsole(true);
        writeGraphic(SYS_GRAPHIC_TYPE_INIT);
        
        for (int i=0; i<3; i++) {
            
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
        std::string data = ""; //TODO: use low level funcs instead of standard lib

        while (hasConsoleData()) {
            const char data_in = (char) Serial.read();
            if (data_in == '\n')
                break;
            else
                data += data_in;
        }
        
        return data.data();
    };
};