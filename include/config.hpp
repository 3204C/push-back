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
extern pros::MotorGroup drivetrain_left;

/// The motors on the right side of the drivetrain.
extern pros::MotorGroup drivetrain_right;

/// The intake motors.
extern pros::MotorGroup intake;

/// The conveyor belt motor.
// extern pros::Motor conveyor;

/// The GPS Sensor.
// extern pros::Gps gps;

/// The AI Vision Sensor.
// extern pros::Vision vision;

#endif
