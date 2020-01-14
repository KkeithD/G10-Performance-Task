#pragma once

class __Indicator {
public:

    void update(bool str);

private:
    void setArmIndicator(bool isArmed);
};

extern __Indicator Indicator;
