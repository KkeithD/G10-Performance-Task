#pragma once

#include <stdint.h>

#define pinT const uint8_t

#define DEFINE_PIN(name, pin, type) static const uint8_t PIN_ ## name = pin; \
                                    static const uint8_t PIN_MODE_ ## name = type;
#define OUT 0x0

#define IN  0x1

DEFINE_PIN(     ARM_CTRL, 0,  IN)    // Alarm Arm (Button) Control
DEFINE_PIN(   ARMED_INDC, 0, OUT)    // Armed LED Indicator
DEFINE_PIN(DISARMED_INDC, 0, OUT)    // Disarmed LED Indicator
DEFINE_PIN(  BUZZER_INDC, 0, OUT)    // Alarm (Buzzer) Indicator
DEFINE_PIN(  MOTION_SENS, 0,  IN)    // Motion (Light) Sensor
DEFINE_PIN(   FLOOD_SENS, 0,  IN)    // Flood (Moisture) Sensor

#undef DEFINE_PIN
#undef OUT
#undef IN
