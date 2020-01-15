#include <arduino.h>
#include <avr/pgmspace.h>

#include <string.h>
#include <stdint.h>

#include "../lib/sha256/sha256.hpp"

#include "graphics.hpp"

#include "pass_sha.hpp"
#include "system.hpp"
#include "settings.hpp"
#include "alarm.hpp"
#include "sensor.hpp"
#include "pin.hpp"

#define INITIALIZE_PIN(name) pinMode(PIN_ ## name, PIN_MODE_ ## name);

uint8_t*      _sys_pass;
Sha256*       _sys_sha256_inst;

uint8_t       _sys_state;
uint8_t       _sys_threat_state;
uint8_t       _sys_threat_level;

char*         _sys_msg;
uint8_t       _sys_msg_len;
bool          _sys_msg_ready;
/*
#include <stdarg.h>
// https://playground.arduino.cc/Main/Printf/
void p(const __FlashStringHelper *fmt, ... ){
  char buf[128]; // resulting string limited to 128 chars
  va_list args;
  va_start (args, fmt);
#ifdef __AVR__
  vsnprintf_P(buf, sizeof(buf), (const char *)fmt, args); // progmem for AVR
#else
  vsnprintf(buf, sizeof(buf), (const char *)fmt, args); // for the rest of the world
#endif
  va_end(args);
  Serial.print(buf);
};*/

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

        _sys_msg = new char[SETTINGS_MAX_MSG_LEN];
        _sys_msg_len = 0;
        _sys_msg_ready = false;

        writeConsole((const __FlashStringHelper *) SYS_GRAPHIC_CALIB);

        uint64_t init_time = getTime();
        while (true) {
            while (!hasConsoleMsg()) {
                calibrateSensors();
                readConsoleMsg();
            }
            writeConsole(getConsoleMsg());
            if (_sys_msg_len == 5 && memcmp("start", getConsoleMsg(), 5) == 0)
                break;
            flushConsoleMsg();
        }
        init_time = getTime() - init_time;

        //flushConsole(true);
        writeGraphic(SYS_GRAPHIC_TYPE_INIT);

//========================================================
        if (init_time < SETTINGS_INIT_STEP_TIME*SETTINGS_INIT_NUM_STEPS) {
            for (int i=0; i<SETTINGS_INIT_NUM_STEPS; i++) {
                uint64_t time_now = getTime();
                playTone(165); //e3, 5000hz
                while (getTime() - time_now < SETTINGS_INIT_STEP_TIME) {
                    calibrateSensors();
                }
                stopTone();
                delay(100);
            };
            playTone(147, 250); delay(50);//F#3
            playTone(185, 250); delay(45);//F#3

            //flushConsole(true);
            writeGraphic(SYS_GRAPHIC_TYPE_WELCOME);

            playTone(220, 250);

            calibrateSensors();
        } else {
            flushConsole(true);
            writeGraphic(SYS_GRAPHIC_TYPE_WELCOME);
        }
//========================================================

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
        writeConsole((const __FlashStringHelper *) SYS_GRAPHIC_FLUSH);
        writeConsole((const __FlashStringHelper *) SYS_GRAPHIC_BASE_TOP);
        switch(graphic_type) {
            case    SYS_GRAPHIC_TYPE_CALIB: writeConsole((const __FlashStringHelper *) SYS_GRAPHIC_CALIB); break;
            case    SYS_GRAPHIC_TYPE_EMPTY: writeConsole((const __FlashStringHelper *) SYS_GRAPHIC_TEXT_EMPTY); break;
            case     SYS_GRAPHIC_TYPE_INIT: writeConsole((const __FlashStringHelper *) SYS_GRAPHIC_TEXT_INIT); break;
            case  SYS_GRAPHIC_TYPE_WELCOME: writeConsole((const __FlashStringHelper *) SYS_GRAPHIC_TEXT_WELCOME); break;
            case    SYS_GRAPHIC_TYPE_ARMED: writeConsole((const __FlashStringHelper *) SYS_GRAPHIC_TEXT_ARMED); break;
            case SYS_GRAPHIC_TYPE_DISARMED: writeConsole((const __FlashStringHelper *) SYS_GRAPHIC_TEXT_DISARMED); break;
            case SYS_GRAPHIC_TYPE_INTRUDER: writeConsole((const __FlashStringHelper *) SYS_GRAPHIC_TEXT_INIT); break;
            case    SYS_GRAPHIC_TYPE_FLOOD: writeConsole((const __FlashStringHelper *) SYS_GRAPHIC_TEXT_FLOOD); break;
        }
        writeConsole((const __FlashStringHelper *) SYS_GRAPHIC_BASE_BOTTOM);
    };

    void readConsoleMsg() {
        while (hasConsoleByte()) {
            const char data = (char) Serial.read();

            if (data == '\n' || _sys_msg_ready == SETTINGS_MAX_MSG_LEN) {
                _sys_msg_ready = true;
            } else {
                memcpy(_sys_msg+_sys_msg_len, &data, 1);
                _sys_msg_len++;
            }
        }
    };

    char* getConsoleMsg() {
        return _sys_msg;
    };

    void flushConsoleMsg() {
        _sys_msg_ready = false;
        _sys_msg_len = 0;
    };

    bool hasConsoleMsg() {
        return _sys_msg_ready;
    };
};