#include <arduino.h>
#include <stdint.h>

#include "control.hpp"
#include "board.hpp"
#include "alarm.hpp"
#include "indicator.hpp"
#include "sensor.hpp"

void setup() {
    Serial.begin(74880);
	Board.init();
	Control.init();
	Alarm.init();
 //pinMode(13, INPUT);
};

void loop() {
  	// put your main code here, to run repeatedly:
	Control.query();
bool threat;
    queryMotionThreat(threat);
    if (threat == 1)
    Serial.println(threat);
  
	Indicator.update(threat);
};
