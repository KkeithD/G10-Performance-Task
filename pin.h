#pragma once

#define pinT const unsigned byte

#define DEFINE_PIN(name, pin) static const unsigned byte name = pin;

DEFINE_PIN(   PIN_ARMED_INDC, 0)    // Armed LED Indicator
DEFINE_PIN(PIN_DISARMED_INDC, 0)    // Disarmed LED Indicator
DEFINE_PIN(  PIN_BUZZER_INDC, 0)    // Alarm (Buzzer) Indicator
DEFINE_PIN(  PIN_MOTION_SENS, 0)    // Motion (Light) Sensor
DEFINE_PIN(   PIN_FLOOD_SENS, 0)    // Flood (Moisture) Sensor

#undef DEFINE_PIN