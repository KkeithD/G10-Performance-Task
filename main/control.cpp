#include "control.hpp"
#include "board.hpp"
#include "pin.hpp"

#include <stdint.h>

void __Control::init() {
    m_armed = ARM_CTRL_OFF;
};

void __Control::query() {
    const bool arm_ctrl_state = Board.readPin(PIN_ARM_CTRL);

    if (m_armed_changed) {
       if (!arm_ctrl_state)
           m_armed_changed = false;
    } else {
        if (arm_ctrl_state) {
            m_armed = !m_armed;
            m_armed_changed = true;
        }
    }
};

__Control Control;
