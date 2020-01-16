#pragma once

#define SYS_INDC_ARMED    0x1
#define SYS_INDC_DISARMED 0x0

#define SYS_INDC_ON       0x1
#define SYS_INDC_OFF      0x0

void init_indicator();

void set_indicator_state(bool is_on, bool is_armed);
