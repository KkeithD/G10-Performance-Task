#include "control.hpp"
#include "board.hpp"
#include "pin.hpp"

#include <stdint.h>

void __Control::init() {
    m_armed = ARM_CTRL_OFF;
    m_arm_changed = false;

    m_light_lvl = 0;
    m_light_lvl_bound = 0;
};

void __Control::query() {
    const bool arm_ctrl_state = !Board.readPin(PIN_ARM_CTRL);
    if (m_armed_changed) {
       if (!arm_ctrl_state) {
           m_armed = !m_armed;
           m_armed_changed = false;
       }
    } else {
        if (arm_ctrl_state)
           m_armed_changed = true;
    }

    const double raw_light_lvl = (double) Board.readAnalogPin(PIN_MOTION_SENS);
    if (raw_light_lvl > raw_light_lvl_bounds)
        raw_light_lvl_bounds = raw_light_lvl;
    m_light_lvl = raw_light_lvl / raw_light_lvl_bounds;
};

__Control Control;
