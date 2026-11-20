#pragma once

#include "main.h"

void arcade_drive_offset(float dir, float turn, float speed);  // Arcade movement scheme
void stop_drive();
bool drive_forward_inches(double inches);
