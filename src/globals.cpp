/*
 * GLOBAL OBJECTS (VARS, CONSTANTS, ROBOT PARTS, ETC.)
 * */

#include "globals.h"

// ---------------------------------------
// GLOABL VARIABLES & CONSTANTS
// ---------------------------------------

std::uint32_t frame_count = 0;
const float ROBOT_SPEED = 1.0f;

// ---------------------------------------
// DEBUG PRINTS
// ---------------------------------------

const int DEBUG_TIMEOUT = 1000;  // Timeout in milliseconds for debug prints

// ---------------------------------------
// ROBOT PARTS
// ---------------------------------------

// Controller
pros::Controller master(pros::E_CONTROLLER_MASTER);

// Chassis
pros::MotorGroup left_main_mg({-1, -10},pros::v5::MotorGears::blue);
pros::MotorGroup right_main_mg({11, 20},pros::v5::MotorGears::blue);

pros::Motor support_left(-2);
pros::Motor support_right(12);

// Sensors
pros::Imu imu_sensor(17);

// Intake

