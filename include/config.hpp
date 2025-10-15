/**
 * @headerfile config.hpp
 * 
 * This file declares the variables for the controller, drivetrain motors,
 * intake motors, conveyor belt motor, GPS Sensor and the AI Vision Sensor.
 */

#ifndef CONFIG_HPP
#define CONFIG_HPP

/// The main controller used for the robot.
extern pros::Controller controller;

/// The motors on the left side of the drivetrain.
extern pros::MotorGroup dt_left;
extern pros::Motor dt_left_front;
extern pros::Motor dt_left_centre;
extern pros::Motor dt_left_back;

/// The motors on the right side of the drivetrain.
extern pros::MotorGroup dt_right;
extern pros::Motor dt_right_front;
extern pros::Motor dt_right_centre;
extern pros::Motor dt_right_back;

/// The intake motors.
extern pros::MotorGroup intake;

/// The conveyor belt motor.
extern pros::Motor conveyor;

/// The GPS Sensor.
extern pros::Gps gps;

/// The Optical Sensor.
// extern pros::Optical optical;

/// The Inertial Sensor.
// extern pros::Imu inertial;

#endif
