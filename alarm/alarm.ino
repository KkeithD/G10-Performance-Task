#include <arduino.h>
#include <stdint.h>

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

};
