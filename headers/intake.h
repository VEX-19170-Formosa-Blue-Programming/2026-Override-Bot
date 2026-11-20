#pragma once

#include "main.h"

// void control_intake(int power);
bool lift_limits_configured();
void control_lift(int power, bool lower_to_ground);