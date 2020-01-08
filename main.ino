#include <arduino.h>
#include "board.h"
#include "control.h"
#include "alarm.h"


void setup() {
    Serial.begin(9600)
	Board.init();
	Control.init();
	Alarm.init();
}

void loop() {
  	// put your main code here, to run repeatedly:
	Control.query();
	Serial.print(Control.isArmed());
}
