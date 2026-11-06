/*
 * DRIVETRAIN FUNCTIONS
 * */

#include "drivetrain.h"
#include "globals.h"
#include <cmath>

// Arcade control scheme

void arcade_drive_offset(float dir, float turn, float speed) {
	const float left_power = std::clamp((dir + turn) * speed, -127.0f, 127.0f);
	const float right_power = std::clamp((dir - turn) * speed, -127.0f, 127.0f);

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

void drive_forward_inches(double inches) {
    // Assumes the motor turns once for each wheel turn.
    const double target_degrees =
        inches / (M_PI * WHEEL_DIAMETER_INCHES) * 360.0;

    left_main_mg.tare_position();
    right_main_mg.tare_position();

    left_main_mg.move_relative(target_degrees, 100);
    right_main_mg.move_relative(target_degrees, 100);
    support_left.move_relative(target_degrees, 100);
    support_right.move_relative(target_degrees, 100);

    // Wait until the main drive encoders are close to their targets.
    while (std::fabs(left_main_mg.get_position() - target_degrees) > ROTATE_TOLERANCE ||
           std::fabs(right_main_mg.get_position() - target_degrees) > ROTATE_TOLERANCE) {
        pros::delay(10);
    }

    stop_drive();
}