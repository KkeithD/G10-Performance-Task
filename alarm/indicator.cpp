#include "indicator.hpp"

#include "system.hpp"
#include "pin.hpp"

void init_indicator() {
    set_indicator_state(SYS_INDC_ON, SYS_INDC_DISARMED);
};

void set_indicator_state(bool is_on, bool is_armed) {
    if (is_on) {
        System::write_pin(   PIN_ARMED_INDC, is_armed);
        System::write_pin(PIN_DISARMED_INDC, !is_armed);
    } else {
        System::write_pin(   PIN_ARMED_INDC, 0);
        System::write_pin(PIN_DISARMED_INDC, 0);
    }
};
