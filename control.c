#include "control.h"
#include "board.h"
#include "pin.h"

void __Control::init() {
    m_armed = ARM_CTRL_OFF;
};

void __Control::query() {
    const bool arm_ctrl_state = Board.readPin(PIN_ARM_CTRL);

    if (m_armed_changed) {
       if (!arm_ctrl_state)
           m_armed_changed = false
    } else {
        if (arm_ctrl_state) {
            m_armed = !m_armed;
            m_armed_changed = true;
        }
    }
};

inline bool __Control::isArmed() {
    return m_armed;
};

inline uint8_t __Control::getThreat() {
    return m_threat;
};

inline uint8_t __Control::getThreatLevel() {
    return m_threat_level;
};

__Control Control;