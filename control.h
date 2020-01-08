#pragma once

#define ARM_CTRL_OFF false
#define ARM_CTRL_ON  true


class __Control {
public:
    void init();

    void query();

    inline bool isArmed();

    inline uint8_t getThreat();

    inline uint8_t getThreatLevel();

private:
    bool m_armed;
    bool m_armed_changed;
}

extern __Control Control;