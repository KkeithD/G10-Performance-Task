#include <arduino.h>
#include <stdint.h>

#include "lib/sha256/sha256.hpp"

#include "src/sensor.hpp"
#include "src/system.hpp"

#include "src/pin.hpp"

void setup() {
    Serial.begin(9600);

  System::initialize();
 //pinMode(13, INPUT);
};

void loop() {
	
};
