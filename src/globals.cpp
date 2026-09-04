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
pros::Motor left_front(-1, pros::v5::MotorGears::blue);
pros::Motor left_middle(-2, pros::v5::MotorGears::red);
pros::Motor left_back(-10, pros::v5::MotorGears::blue);

pros::Motor right_front(11, pros::v5::MotorGears::blue);
pros::Motor right_front_middle(12,pros::v5::MotorGears::red);
pros::Motor right_front_back(20, pros::v5::MotorGears::blue);

pros::MotorGroup left_mg({left_front, left_middle, left_back});
pros::MotorGroup right_mg({right_front, right_front_middle, right_front_back});

// Sensors
pros::Imu imu_sensor(17);

// Intake
pros::MotorGroup intake({9, -10}, pros::v5::MotorGears::blue);

// Lift
pros::MotorGroup lift({7, -8}, pros::v5::MotorGears::blue);