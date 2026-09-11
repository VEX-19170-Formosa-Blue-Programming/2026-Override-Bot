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
extern pros::Motor m1;
extern pros::Motor m2;
extern pros::Motor m3;


extern pros::MotorGroup left_mg;
extern pros::MotorGroup right_mg;

extern pros::Imu imu_sensor;

extern pros::MotorGroup intake;
extern pros::MotorGroup lift;