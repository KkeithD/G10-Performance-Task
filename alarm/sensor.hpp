#pragma once

#include <stdint.h>

void init_sensors();

void calib_sensors();

bool get_motion_threat();

bool get_flood_threat();
