 /*
 * TO ADJUST ROBOT SETTINGS, GO TO globals.cpp
 * */

/*
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 * */

// Framework files
#include "main.h"

// Headers
#include "drivetrain.h"
#include "globals.h"
#include "intake.h"

#include <algorithm>
#include <cmath>

// https://pros.cs.purdue.edu/v5/api/cpp/motors.html

// A callback function for LLEMU's center button.
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/*
 * Runs initialization code
 *
 * All other competition modes are blocked by initialize
 */
void initialize() {
	imu_sensor.reset();
	pros::delay(1000);
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/*
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {

}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {

}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

// Entry point for autonomous function (used for manual/testing invocation from opcontrol)

void run_autonomous() {
	autonomous();
}

void autonomous() {

	pros::lcd::set_text(3, "Autonomous mode initialized");

	frame_count = 0;  // Reset frame count
	const float auton_time_limit = 10.0f;  // Time in seconds for autonomous mode

	while (true) {
		float elapsed = frame_count * 0.02f;
		if (elapsed >= auton_time_limit) {
			break;
		}

		if (master.get_digital(DIGITAL_UP)) {
			stop_drive();
			pros::lcd::set_text(3, "User-controlled mode initialized");
			return;  // Exit autonomous mode early if the up button is pressed
		}

		// Move the robot in a circle.
		// mult by 127 to match the -127..127 range
		arcade_drive_offset(sin(frame_count * 0.1) * 127.0, cos(frame_count * 0.1) * 127.0, ROBOT_SPEED);

		pros::lcd::set_text(4, "Time left: " + std::to_string(auton_time_limit - elapsed) + " seconds");

		pros::delay(20);
		frame_count++;
	}
	stop_drive();

	pros::lcd::set_text(4, "Autonomous mode complete");

	int countdown = 3;
	while (countdown > 0) {
		pros::lcd::set_text(5, "Return to opcontrol in " + std::to_string(countdown) + " seconds...");
		pros::delay(1000);
		countdown--;
	}
	pros::lcd::clear_line(5);
	pros::lcd::set_text(3, "User-controlled mode initialized");
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 */

void opcontrol() {

	// User-controlled mode
	pros::lcd::set_text(3, "User-controlled mode initialized");
	std::uint32_t last_lcd_update = 0;

	while (true) {
		// Handle controller connection status
		if (!master.is_connected()) {
			pros::delay(20);
			continue;
		}


		// Get user input
		int dir = master.get_analog(ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
		int turn = master.get_analog(ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick
		arcade_drive_offset(dir, turn, ROBOT_SPEED);

		const int intake_power = master.get_digital(DIGITAL_R1) ? 127 :
			master.get_digital(DIGITAL_R2) ? -127 : 0;
		const int lift_power = master.get_digital(DIGITAL_L1) ? 127 :
			master.get_digital(DIGITAL_L2) ? -127 : 0;
		control_intake(intake_power);
		control_lift(lift_power);

		// Update diagnostics less often so LCD and sensor reads cannot delay control.
		if (pros::millis() - last_lcd_update >= DEBUG_TIMEOUT) {
			auto velocity_list = left_mg.get_actual_velocity_all();
			auto right_velocity_list = right_mg.get_actual_velocity_all();
			velocity_list.insert(velocity_list.end(), right_velocity_list.begin(), right_velocity_list.end());

			for (std::size_t i = 0; i < velocity_list.size() && i < 8; i++) {
				pros::lcd::print(static_cast<int>(i), "Motor %d: %.1f", static_cast<int>(i + 1), velocity_list[i]);
			}
			last_lcd_update = pros::millis();
		}

		pros::delay(20);
		
	}
}
