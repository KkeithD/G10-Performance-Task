#include <arduino.h>
#include <stdint.h>

#include "settings.hpp"
#include "system.hpp"

#include "sha256.hpp"

void setup() {
    Serial.begin(SETTINGS_SERIAL_BAUD_RATE);
    System::initialize();
};

void loop() {
    System::query();
};
