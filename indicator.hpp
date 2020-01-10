#pragma once

class __Indicator {
public:

    void update();

private:
    void setArmIndicator(bool isArmed);
};

extern __Indicator Indicator;
