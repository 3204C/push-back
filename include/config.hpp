/**
 * @headerfile config.hpp
 * 
 * This file declares the variables for the controller, drivetrain motors,
 * intake motors, conveyor belt motor, GPS Sensor and the AI Vision Sensor.
 */

#ifndef CONFIG_HPP
#define CONFIG_HPP

/// @brief The main controller used for the robot.
extern pros::Controller controller;

/// @brief The motors on the left side of the drivetrain.
extern pros::MotorGroup dt_left;

/// @brief The motors on the right side of the drivetrain.
extern pros::MotorGroup dt_right;

/// @brief The intake motors.
extern pros::MotorGroup intake;

/// @brief The conveyor belt motor.
extern pros::Motor conveyor;

/// @brief The outtake motor.
extern pros::Motor outtake;

/// @brief The pneumatics for the outtake.
extern pros::ADIDigitalOut pneumatics;

/// @brief The GPS Sensor.
// extern pros::Gps gps;

/// @brief The Optical Sensor.
// extern pros::Optical optical;

/// @brief The Inertial Sensor.
// extern pros::Imu inertial;

#endif
