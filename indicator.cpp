#include "indicator.hpp"
#include "control.hpp"
#include "board.hpp"
#include "pin.hpp"
#include "Arduino.h"

void __Indicator::update() {
  
    Serial.println(Control.isArmed());
    setArmIndicator(Control.isArmed());
}

void __Indicator::setArmIndicator(bool isArmed) {
    Board.writePin(   PIN_ARMED_INDC, isArmed);
    Board.writePin(PIN_DISARMED_INDC, !isArmed);
}
__Indicator Indicator;
