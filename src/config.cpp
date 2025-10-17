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
pros::Motor dt_left_front(dt_left.get_port(0));
pros::Motor dt_left_centre(dt_left.get_port(1));
pros::Motor dt_left_back(dt_left.get_port(2));

pros::MotorGroup dt_right({-6, 5, -4});
pros::Motor dt_right_front(dt_right.get_port(0));
pros::Motor dt_right_centre(dt_right.get_port(1));
pros::Motor dt_right_back(dt_right.get_port(2));

pros::MotorGroup intake({10, -21});

pros::Motor conveyor(-9);

pros::Motor outtake(-7);

// TODO: Change port number and offset placeholders
pros::Gps gps(18, 0.0, 0.0);

// TODO: Change port number placeholder
// pros::Optical optical();

// TODO: Change port number placeholder
// pros::Imu inertial();
