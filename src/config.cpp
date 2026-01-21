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

pros::Motor conveyor(-9);

pros::Motor outtake(-7);

pros::ADIDigitalOut pneumatics('F');

// TODO: Change offset placeholders
pros::Gps gps(19, 0.0, 0.0);

pros::Optical optical(18);

pros::Imu inertial(11);
