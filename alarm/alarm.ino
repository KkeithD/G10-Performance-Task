#include <arduino.h>
#include <stdint.h>

<<<<<<< HEAD
#include "lib/sha256/sha256.hpp"
#include <avr/pgmspace.h>
#include "src/sensor.hpp"
#include "src/system.hpp"
#include "src/graphics.hpp"
//#include "src/pin.hpp"

void setup() {
    Serial.begin(9600);

  System::initialize();
  
        //Serial.println ((const __FlashStringHelper *) SYS_GRAPHIC_CALIB);
 //pinMode(13, INPUT);
};

void loop() {

=======
#include "system.hpp"
#include "sensor.hpp"
#include "graphics.hpp"
#include "settings.hpp"

void setup() {
    Serial.begin(SETTINGS_SERIAL_BAUD_RATE);
    System::initialize();
};

void loop() {
    System::query();
>>>>>>> night push
};
