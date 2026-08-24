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

void autonomous() {

	pros::lcd::set_text(3, "Autonomous mode initialized");

	while (frame_count < 1000) {

		// Move the robot in a circle
		arcade_drive_offset(sin(frame_count * 0.1), cos(frame_count * 0.1));
		pros::delay(20);

		frame_count++;
		pros::lcd::set_text(4, "Frame count: " + std::to_string(frame_count));
	}
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

	if (false) {
		// User-controlled mode
		pros::lcd::set_text(3, "User-controlled mode initialized");

		while (true) {
			// Get user input
			int dir = master.get_analog(ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
			int turn = master.get_analog(ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick
			arcade_drive_offset(dir, turn);
		}
	} else {
		// Autonomous mode
		autonomous();
	}

	pros::delay(20);
}
