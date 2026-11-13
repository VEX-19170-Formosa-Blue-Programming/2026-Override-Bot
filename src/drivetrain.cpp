/*
 * DRIVETRAIN FUNCTIONS
 * */

#include "drivetrain.h"
#include "globals.h"
#include <algorithm>
#include <cmath>

namespace {

double average_left_position() {
	return (left_main_mg.get_position() + support_left.get_position()) / 2.0;
}

double average_right_position() {
	return (right_main_mg.get_position() + support_right.get_position()) / 2.0;
}

double calculate_pid_output(double error, double dt, double &integral,
                            double &previous_error) {
	if (DRIVE_PID_KI != 0.0f) {
		const double max_integral =
			DRIVE_PID_MAX_INTEGRAL_OUTPUT / std::fabs(DRIVE_PID_KI);
		integral = std::clamp(integral + error * dt, -max_integral, max_integral);
	}

	const double derivative = (error - previous_error) / dt;
	previous_error = error;
	return DRIVE_PID_KP * error + DRIVE_PID_KI * integral +
		DRIVE_PID_KD * derivative;
}

}  // namespace

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

bool drive_forward_inches(double inches) {
    // Assumes the motor turns once for each wheel turn.
    const double target_degrees =
        inches / (M_PI * WHEEL_DIAMETER_INCHES) * 360.0;

    left_main_mg.tare_position();
    right_main_mg.tare_position();
    support_left.tare_position();
    support_right.tare_position();

    double left_integral = 0.0;
    double right_integral = 0.0;
    double left_previous_error = target_degrees;
    double right_previous_error = target_degrees;
    std::uint32_t previous_time = pros::millis();
    const std::uint32_t start_time = previous_time;
    std::uint32_t settled_since = 0;
    bool settling = false;

    while (pros::millis() - start_time < DRIVE_PID_TIMEOUT_MS) {
        const std::uint32_t now = pros::millis();
        const double dt = std::max(
            (now - previous_time) / 1000.0, 0.001);
        previous_time = now;

        const double left_error = target_degrees - average_left_position();
        const double right_error = target_degrees - average_right_position();
        const bool left_in_tolerance = std::fabs(left_error) <= ROTATE_TOLERANCE;
        const bool right_in_tolerance = std::fabs(right_error) <= ROTATE_TOLERANCE;
        if (left_in_tolerance) {
            left_previous_error = left_error;
        }
        if (right_in_tolerance) {
            right_previous_error = right_error;
        }

        if (left_in_tolerance && right_in_tolerance) {
            stop_drive();
            if (!settling) {
                settled_since = now;
                settling = true;
            } else if (now - settled_since >= DRIVE_PID_SETTLE_TIME_MS) {
                stop_drive();
                return true;
            }
        } else {
            settling = false;
            const double left_output = left_in_tolerance ? 0.0 :
                calculate_pid_output(left_error, dt, left_integral, left_previous_error);
            const double right_output = right_in_tolerance ? 0.0 :
                calculate_pid_output(right_error, dt, right_integral, right_previous_error);
            if (left_in_tolerance) {
                left_main_mg.brake();
                support_left.brake();
            } else {
                const int power = static_cast<int>(
                    std::lround(std::clamp(
                        left_output, -static_cast<double>(DRIVE_PID_MAX_POWER),
                        static_cast<double>(DRIVE_PID_MAX_POWER))));
                left_main_mg.move(power);
                support_left.move(power);
            }
            if (right_in_tolerance) {
                right_main_mg.brake();
                support_right.brake();
            } else {
                const int power = static_cast<int>(
                    std::lround(std::clamp(
                        right_output, -static_cast<double>(DRIVE_PID_MAX_POWER),
                        static_cast<double>(DRIVE_PID_MAX_POWER))));
                right_main_mg.move(power);
                support_right.move(power);
            }
        }

        pros::delay(10);
    }

    stop_drive();
    return false;
}