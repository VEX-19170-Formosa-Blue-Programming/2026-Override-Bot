#pragma once

#include "main.h"
#include <cstdint>

// ---------------------------------------
// GLOBAL VARIABLES & CONSTANTS
// ---------------------------------------

extern std::uint32_t frame_count;
extern const float ROBOT_SPEED;

// ---------------------------------------
// DEBUG PRINTS
// ---------------------------------------

extern const int DEBUG_TIMEOUT;

// ---------------------------------------
// ROBOT PARTS
// ---------------------------------------

extern pros::Controller master;

extern pros::Motor support_left;
extern pros::Motor support_right;

extern pros::MotorGroup left_main_mg;
extern pros::MotorGroup right_main_mg;

extern pros::Imu imu_sensor;

