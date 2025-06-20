/**
 * @file config.cpp
 * 
 * This file defines all variables declared in "config.hpp". These variables
 * define the controller, drivetrain motors, intake motors, conveyor belt motor,
 * GPS Sensor and the AI Vision Sensor.
 */

#include "main.h"

pros::Controller controller(CONTROLLER_MASTER);

pros::MotorGroup drivetrain_left({13, 12, 11});

pros::MotorGroup drivetrain_right({-18, -19, -20});

pros::MotorGroup intake({14, -17});

// TODO: Change port number placeholder
pros::Motor conveyor(1);

// TODO: Change port number and offset placeholders
pros::Gps gps(2, 0.0, 0.0);

// TODO: Change port number placeholder
pros::Vision vision(3);
