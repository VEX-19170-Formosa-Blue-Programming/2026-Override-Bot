/*
 * DRIVETRAIN FUNCTIONS
 * */

#include "drivetrain.h"
#include "globals.h"

// Arcade control scheme

void arcade_drive_offset(float dir, float turn, float speed) {
	const float left_power = std::clamp((dir - turn) * speed, -127.0f, 127.0f);
	const float right_power = std::clamp((dir + turn) * speed, -127.0f, 127.0f);

	left_mg.move(left_power);
	right_mg.move(right_power);
}

void stop_drive() {
	left_mg.brake();
	right_mg.brake();
}