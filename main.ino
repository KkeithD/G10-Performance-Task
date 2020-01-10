#include <arduino.h>
#include <stdint.h>

#include "control.hpp"
#include "board.hpp"
#include "alarm.hpp"
#include "indicator.hpp"

void setup() {
    Serial.begin(9600);
	Board.init();
	Control.init();
	Alarm.init();
 //pinMode(13, INPUT);
};

void loop() {
  	// put your main code here, to run repeatedly:
	Control.query();
	Indicator.update();
};
