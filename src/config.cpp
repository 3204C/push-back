/**
 * @file config.cpp
 * 
 * This file defines all variables declared in "config.hpp". These variables
 * define the controller, drivetrain motors, intake motor, GPS Sensor and the
 * AI Vision Sensor.
 */


#include "main.h"


pros::Controller controller(CONTROLLER_MASTER);

// TODO: Change port number placeholders
pros::MotorGroup drivetrain_left({1, 2, 3});

// TODO: Change port number placeholders
pros::MotorGroup drivetrain_right({4, 5, 6});

// TODO: Change port number placeholder
pros::Motor intake(7);

// TODO: Change port number and offset placeholders
pros::Gps gps(8, 0.0, 0.0);

// TODO: Change port number placeholder
pros::Vision vision(9);
