/**
 * @headerfile drivetrain.hpp
 * 
 * This file declares all variables and functions used for the drivetrain's
 * autonomous and driver control movement. Some functions utilise the VEX V5
 * GPS Sensor to identify the robot's position and heading on the field.
 */

#ifndef DRIVETRAIN_HPP
#define DRIVETRAIN_HPP

/**
 * Controls the drivetrain motors using voltage. Used for driver control.
 * 
 * @param left_voltage The voltage of each motor on the left side of the drivetrain.
 * @param right_voltage The voltage of each motor on the right side of the drivetrain.
 * @param min_voltage The minimum voltage required to spin the motors.
 */
void dt_move(int left_voltage, int right_voltage, int min_voltage);

/**
 * Controls the drivetrain motors using voltage for an amount of time.
 * Used for autonomous.
 * 
 * @param left_voltage The voltage of each motor on the left side of the drivetrain.
 * @param right_voltage The voltage of each motor on the right side of the drivetrain.
 * @param min_voltage The minimum voltage required to spin the motors.
 * @param duration The amount of time (in ms) the drivetrain motors spin for.
 */
void dt_move(int left_voltage, int right_voltage, int min_voltage, int duration);

/**
 * Moves the drivetrain in a straight line for a given distance and duration of time.
 * 
 * @param distance The length of displacement from the robot's original position (in inches).
 * @param duration The amount of time (in ms) the drivetrain motors spin for.
 */
void dt_move_straight(double distance, int duration);

/**
 * Turns the drivetrain at a given angle and for a duration of time.
 * 
 * @param angle The angular displacement from the robot's original orientation (in degrees).
 * @param duration The amount of time (in ms) the drivetrain motors spin for.
 */
void dt_turn(double angle, int duration);

#endif
