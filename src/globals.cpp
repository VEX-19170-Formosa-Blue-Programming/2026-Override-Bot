#include "globals.h"

uint frame_count = 0;

//Controller
pros::Controller master(pros::E_CONTROLLER_MASTER);


// Chassis
pros::MotorGroup left_mg({1, -2, 3});
pros::MotorGroup right_mg({-4, 5, -6});

// Sensors
pros::Imu imu_sensor(17);

// Intake
pros::MotorGroup intake({9, -10});

// Lift
pros::MotorGroup lift({7, -8});