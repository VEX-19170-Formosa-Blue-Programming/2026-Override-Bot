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

pros::Motor m1(-1, pros::E_MOTOR_GEAR_BLUE);
pros::Motor m2(-2, pros::E_MOTOR_GEAR_GREEN);
pros::Motor m3(-10, pros::E_MOTOR_GEAR_BLUE);

pros::MotorGroup left_mg({-1,-2, -10});
pros::MotorGroup right_mg({11, 12, 20});

// Sensors
pros::Imu imu_sensor(17);

// Intake

// Lift
pros::MotorGroup lift({7, -8}, pros::v5::MotorGears::blue);