#include <arduino.h>
#include <avr/pgmspace.h>

#include <string.h>
#include <stdint.h>
//#include "sha256.hpp"

#include "graphics.hpp"

#include "sha_pass.hpp"
#include "system.hpp"
#include "settings.hpp"
#include "indicator.hpp"
#include "control.hpp"
#include "alarm.hpp"
#include "sensor.hpp"
#include "pin.hpp"

#define INITIALIZE_PIN(name) pinMode(PIN_ ## name, PIN_MODE_ ## name);

uint8_t       _sys_pass_hash[SHA256_BLOCK_SIZE];

uint8_t _sys_state;
uint8_t _sys_threat_state;
uint8_t _sys_threat_level;

char*   _sys_msg;
uint8_t _sys_msg_len;
bool    _sys_msg_ready;

void set_sys_state(uint8_t state) {
    _sys_state = state;
};

uint8_t get_sys_state() {
    return _sys_state;
};

inline void write_console(char* data) {
    Serial.println(data);
};

inline void flush_console() {
    Serial.println("\n");
    Serial.flush();
};

inline bool is_console_available() {
    return Serial.available() > 0;
};

inline void write_graphic(const char* graphic) {
    Serial.println((const __FlashStringHelper*) graphic);
};

void write_alarm_graphic(const char* banner_graphic, const char* alert_graphic) {
    flush_console();
    write_graphic(SYS_GRAPHIC_BASE_TOP);
    write_graphic(banner_graphic);
    write_graphic(SYS_GRAPHIC_BASE_MID);
    write_graphic(alert_graphic);
    write_graphic(SYS_GRAPHIC_BASE_BOTTOM);
};

void read_console_data() {
    while (is_console_available()) {
        const char data = (char) Serial.read();

        if (data == '\n' || _sys_msg_ready == SETTINGS_MAX_MSG_LEN) {
            _sys_msg_ready = true;
        } else {
            memcpy(_sys_msg+_sys_msg_len, &data, 1);
            _sys_msg_len++;
        }
    }
};

void flush_console_msg() {
    _sys_msg_ready = false;
    _sys_msg_len = 0;
};

void operate_neutral() {
    while(get_sys_state() == SYS_STATE_NEUTRAL) {
        uint8_t control_tick = 0,
                last_control_tick = 0;
                
        while ((control_tick = query_control()) > 0) {
            calib_sensors();
            if(control_tick != last_control_tick) {
                switch(control_tick) {
                    case 1: write_alarm_graphic(SYS_GRAPHIC_BANNER_ARMING0, SYS_GRAPHIC_ALERT_EMPTY);  break;
                    case 2: write_alarm_graphic(SYS_GRAPHIC_BANNER_ARMING1, SYS_GRAPHIC_ALERT_EMPTY);  break;
                    case 3: write_alarm_graphic(SYS_GRAPHIC_BANNER_ARMING2, SYS_GRAPHIC_ALERT_EMPTY);  break;
                    case 4: write_alarm_graphic(SYS_GRAPHIC_BANNER_ARMING3, SYS_GRAPHIC_ALERT_EMPTY);  break;
                }
            }
                
            if (control_tick > SETTINGS_ARM_TICK_COUNT) {
                reset_control();
                set_sys_state(SYS_STATE_ARMED);
                break;
            }
            last_control_tick = control_tick;
        }

        if (last_control_tick != 0 && control_tick == 0) {
            uint64_t time_last = System::get_time();
            
            while (System::get_time() - time_last < 400)
                calib_sensors();
                
            write_alarm_graphic(SYS_GRAPHIC_BANNER_EMPTY, SYS_GRAPHIC_ALERT_EMPTY);
            
            time_last = System::get_time();
            while (System::get_time() - time_last < 400)
                calib_sensors();
                
            write_alarm_graphic(SYS_GRAPHIC_BANNER_CANCELLED, SYS_GRAPHIC_ALERT_EMPTY);
            time_last = System::get_time();

            time_last = System::get_time();
            while (System::get_time() - time_last < 400)
                calib_sensors();
            
            write_alarm_graphic(SYS_GRAPHIC_BANNER_EMPTY, SYS_GRAPHIC_ALERT_EMPTY);
        }
        calib_sensors();
    }
};

bool check_console_hash() {
    uint8_t pass_hash[SHA256_BLOCK_SIZE];

    SHA256_CTX ctx;
        ctx.datalen = 0;
        ctx.bitlen = 512;
        
    sha256_init(&ctx);
    sha256_update(&ctx, _sys_msg, _sys_msg_len);
    sha256_final(&ctx, pass_hash);

    flush_console_msg();

    return memcmp(pass_hash, _sys_pass_hash, SHA256_BLOCK_SIZE) == 0;
};

bool check_console_seq() {
    const uint64_t time_last = System::get_time();
    while (System::get_time() - time_last < 400) {
        read_console_data();
        if (_sys_msg_ready) {
            if (check_console_hash()) {
                return true;
            } else {
                while (System::get_time() - time_last < 400) {
                    calib_sensors();
                }
            } 
            return false;
        }
    }
    return false;
};

bool run_alarm_seq(const char* alert_graphic) {
    alarm_play_tone(5000);
    write_alarm_graphic(SYS_GRAPHIC_BANNER_EMPTY, alert_graphic);

    //delay(400)
    if (check_console_seq()) {
        alarm_stop_tone();
        return true;
    }
    
    alarm_stop_tone();
    write_alarm_graphic(SYS_GRAPHIC_BANNER_EMPTY, SYS_GRAPHIC_ALERT_EMPTY);
    
    return check_console_seq();
};

void operate_armed() {
    for (int i=0; i<SETTINGS_ARMED_TICK_COUNT; i++) {
        alarm_play_tone(659); //e4, 5000hz
        
        uint64_t last_time = System::get_time();
        while (System::get_time() - last_time < SETTINGS_ARMED_TICK_TIME)
            calib_sensors();
        alarm_stop_tone();
            
        if (i == SETTINGS_ARMED_TICK_COUNT-1)
            write_alarm_graphic(SYS_GRAPHIC_BANNER_EMPTY, SYS_GRAPHIC_ALERT_EMPTY);
    }
    
    write_alarm_graphic(SYS_GRAPHIC_BANNER_ARMED, SYS_GRAPHIC_ALERT_EMPTY);
    set_indicator_state(SYS_INDC_ON, SYS_INDC_ARMED);
    alarm_play_tone(147, 200); alarm_play_tone(185, 200); alarm_play_tone(220, 250); alarm_play_tone(147, 200);
    write_alarm_graphic(SYS_GRAPHIC_BANNER_EMPTY, SYS_GRAPHIC_ALERT_EMPTY);
    calib_sensors();

    uint8_t threat_flag = SYS_THREAT_NONE;
    while (get_sys_state() == SYS_STATE_ARMED) {
        read_console_data();
        if (_sys_msg_ready) {
            if (check_console_hash())
                break;
        }
      
        if ((threat_flag & SYS_THREAT_MOTION) == 0 && get_motion_threat())
            threat_flag |= SYS_THREAT_MOTION;
            
        if ((threat_flag & SYS_THREAT_FLOOD) == 0 && get_flood_threat())
            threat_flag |= SYS_THREAT_FLOOD;

        if (threat_flag != SYS_THREAT_NONE) {
            if (run_alarm_seq(SYS_GRAPHIC_ALERT_THREAT)) break;
            
            if ((threat_flag & SYS_THREAT_MOTION) == SYS_THREAT_MOTION)
                if (run_alarm_seq(SYS_GRAPHIC_ALERT_MOTION)) break;
            
            if ((threat_flag & SYS_THREAT_FLOOD) == SYS_THREAT_FLOOD)
                if (run_alarm_seq(SYS_GRAPHIC_ALERT_FLOOD)) break;
        }
    }
    set_sys_state(SYS_STATE_DISARMED);
};

void operate_disarmed() {
    write_alarm_graphic(SYS_GRAPHIC_BANNER_DISARMED, SYS_GRAPHIC_ALERT_EMPTY);
    set_indicator_state(SYS_INDC_ON, SYS_INDC_DISARMED);
    alarm_play_tone(220, 200); alarm_play_tone(185, 200); alarm_play_tone(147, 250);
    delay(500);
    write_alarm_graphic(SYS_GRAPHIC_BANNER_EMPTY, SYS_GRAPHIC_ALERT_EMPTY);
    set_sys_state(SYS_STATE_NEUTRAL);
};

namespace System {
    void initialize() {
        INITIALIZE_PIN(      ARM_CTRL )
        INITIALIZE_PIN(    ARMED_INDC )
        INITIALIZE_PIN( DISARMED_INDC )
        INITIALIZE_PIN(   BUZZER_INDC )
        INITIALIZE_PIN(   MOTION_SENS )
        INITIALIZE_PIN(    FLOOD_SENS )

        _sys_state = SYS_STATE_INIT;

        __get_sys_pass_hash(_sys_pass_hash);
        
        _sys_msg = new char[SETTINGS_MAX_MSG_LEN];
        _sys_msg_len = 0;
        _sys_msg_ready = false;

        write_graphic(SYS_GRAPHIC_CALIB);

        init_sensors();
        init_control();

        while (true) {
            while (!_sys_msg_ready) {
                calib_sensors();
                read_console_data();
            }
            if (_sys_msg_len == 5 && memcmp("start", _sys_msg, 5) == 0)
                break;
            flush_console_msg();
        };
        flush_console_msg();
        
        set_sys_state(SYS_STATE_INIT);
        write_alarm_graphic(SYS_GRAPHIC_BANNER_INIT, SYS_GRAPHIC_ALERT_EMPTY);
        
        for (int i=0; i<SETTINGS_INIT_NUM_STEPS; i++) {
            uint64_t last_time = get_time();
            alarm_play_tone(659); //e4, 5000hz
            while (System::get_time() - last_time < SETTINGS_INIT_STEP_TIME)
                calib_sensors();
            alarm_stop_tone();
            delay((i == SETTINGS_INIT_NUM_STEPS-1) ? 100 : 200);
        }
        
        write_alarm_graphic(SYS_GRAPHIC_BANNER_EMPTY, SYS_GRAPHIC_ALERT_EMPTY);
        delay(100);
        write_alarm_graphic(SYS_GRAPHIC_BANNER_WELCOME, SYS_GRAPHIC_ALERT_EMPTY);
        alarm_play_tone(147, 200); alarm_play_tone(185, 200); alarm_play_tone(220, 250);
        delay(800);
        write_alarm_graphic(SYS_GRAPHIC_BANNER_EMPTY, SYS_GRAPHIC_ALERT_EMPTY);

        set_indicator_state(SYS_INDC_ON, SYS_INDC_DISARMED);
        set_sys_state(SYS_STATE_NEUTRAL);
    };

    void query() {
        switch(get_sys_state()) {
            case SYS_STATE_NEUTRAL: {
                operate_neutral();
                break;
            }
            case SYS_STATE_ARMED: {
                operate_armed();
                break;
            }
            case SYS_STATE_DISARMED: {
                operate_disarmed();
                break;
            }
        }
    }
};
