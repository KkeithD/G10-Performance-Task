#pragma once

#include <pins_arduino.h>
#include <stdint.h>

#define DEFINE_PIN(name, pin, type) static const uint8_t PIN_ ## name = pin; \
                                    static const uint8_t PIN_MODE_ ## name = type;
#define OUT 0x1
#define IN  0x0

    DEFINE_PIN(       ARM_CTRL, 13,  IN  )    // Alarm Arm (Button) Control
    DEFINE_PIN(     ARMED_INDC,  3, OUT  )    // Armed LED Indicator
    DEFINE_PIN(  DISARMED_INDC,  4, OUT  )    // Disarmed LED Indicator
    DEFINE_PIN(    BUZZER_INDC, 11, OUT  )    // Alarm (Buzzer) Indicator
    DEFINE_PIN(    MOTION_SENS, A0,  IN  )    // Motion (Light) Sensor
    DEFINE_PIN(     FLOOD_SENS,  0,  IN  )    // Flood (Moisture) Sensor

#undef OUT
#undef IN
#undef DEFINE_PIN
