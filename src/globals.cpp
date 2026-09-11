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
// ROBOT PARTS
// ---------------------------------------

// Controller
pros::Controller master(pros::E_CONTROLLER_MASTER);

// Chassis
pros::MotorGroup left_mg({-1, -2, -10});
pros::MotorGroup right_mg({11, 12, 20});

// Sensors
pros::Imu imu_sensor(17);

// Intake
pros::MotorGroup intake({9, -10}, pros::v5::MotorGears::blue);

// Lift
pros::MotorGroup lift({7, -8}, pros::v5::MotorGears::blue);