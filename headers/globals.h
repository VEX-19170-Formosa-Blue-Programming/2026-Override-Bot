#pragma once

#include "main.h"
#include <cstdint>

// ---------------------------------------
// GLOABL VARIABLES & CONSTANTS
// ---------------------------------------

extern std::uint32_t frame_count;
extern const float ROBOT_SPEED;

// ---------------------------------------
// ROBOT PARTS
// ---------------------------------------

extern pros::Controller master;

extern pros::Motor left_front;
extern pros::Motor left_middle;
extern pros::Motor left_back;

extern pros::Motor right_front;
extern pros::Motor right_front_middle;
extern pros::Motor right_front_back;

extern pros::MotorGroup left_mg;
extern pros::MotorGroup right_mg;

extern pros::Imu imu_sensor;

extern pros::MotorGroup intake;
extern pros::MotorGroup lift;