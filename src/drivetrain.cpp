/*
 * DRIVETRAIN FUNCTIONS
 * */

#include "drivetrain.h"
#include "globals.h"

// Arcade control scheme

void arcade_drive_offset(float dir, float turn, float speed) {
	const float left_power = std::clamp((dir - turn) * speed, -127.0f, 127.0f);
	const float right_power = std::clamp((dir + turn) * speed, -127.0f, 127.0f);

	left_main_mg.move(left_power);
	right_main_mg.move(right_power);

	support_left.move(left_power);
	support_right.move(right_power);

}

void stop_drive() {
	left_main_mg.brake();
	right_main_mg.brake();

	support_left.brake();
	support_right.brake();
}