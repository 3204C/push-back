/**
 * @file config.cpp
 * 
 * This file defines all variables declared in "config.hpp". These variables
 * define the controller, drivetrain motors, intake motor, GPS Sensor and the
 * AI Vision Sensor.
 */


#include "main.h"


pros::Controller controller(CONTROLLER_MASTER);

pros::MotorGroup drivetrain_left({20, 19, 18});

pros::MotorGroup drivetrain_right({-11, -12, -13});

// TODO: Change port number placeholder
pros::Motor intake(1);

// TODO: Change port number and offset placeholders
pros::Gps gps(2, 0.0, 0.0);

// TODO: Change port number placeholder
pros::Vision vision(3);
