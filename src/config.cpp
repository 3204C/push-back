/**
 * @file config.cpp
 * 
 * This file defines all variables declared in "config.hpp". These variables
 * define the controller, drivetrain motors, intake motors, conveyor belt motor,
 * GPS Sensor and the AI Vision Sensor.
 */

#include "main.h"

pros::Controller controller(CONTROLLER_MASTER);

pros::MotorGroup dt_left({3, -2, 1});

pros::MotorGroup dt_right({-6, 5, -4});

pros::MotorGroup intake({10, -21});

// TODO: Change port number placeholders
pros::MotorGroup conveyor({16, -17});

// TODO: Change port number and offset placeholders
pros::Gps gps(18, 0.0, 0.0);

// TODO: Change port number placeholder
// pros::Optical optical(19);

// TODO: Change port number placeholder
// pros::Vision vision(20);
