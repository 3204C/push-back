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
 * Returns the distance between the robot and a given point (x, y) (in inches).
 * 
 * @param x, y The coordinates of the point.
 * @returns The distance between the robot and the point (x, y) (in inches).
 */
double distance_to_point(double x, double y);

/**
 * Returns the heading of a point (x, y) from the robot's position (in degrees).
 * 
 * @param x, y The coordinates of the point.
 * @returns The heading of the point (x, y) from the robot's position.
 */
double heading_from_robot(double x, double y);

/**
 * Returns the smallest angle that the robot can turn to face a point (x, y) (in degrees).
 * 
 * @param x, y The coordinates of the point.
 * @returns The smallest angle that the robot can turn to face the point (x, y) (in degrees).
 */
double angle_from_robot(double x, double y);

/**
 * Controls the drivetrain motors using voltage. Used for driver control.
 * 
 * @param left_voltage The voltage of each motor on the left side of the drivetrain.
 * @param right_voltage The voltage of each motor on the right side of the drivetrain.
 * @param min_voltage The minimum voltage required to spin the motors.
 * @param max_voltage The maximum voltage that the motors can reach.
 */
void dt_move_voltage(int left_voltage, int right_voltage, int min_voltage, int max_voltage);

/**
 * Controls the drivetrain motors using voltage for an amount of time.
 * Used for autonomous.
 * 
 * @param left_voltage The voltage of each motor on the left side of the drivetrain.
 * @param right_voltage The voltage of each motor on the right side of the drivetrain.
 * @param min_voltage The minimum voltage required to spin the motors.
 * @param max_voltage The maximum voltage that the motors can reach.
 * @param duration The time it takes for the robot to move (in ms).
 */
void dt_move_voltage(int left_voltage, int right_voltage, int min_voltage, int max_voltage, int duration);

/**
 * Turns the drivetrain at a given angle for a duration of time.
 * 
 * @param angle The angular displacement from the robot's original orientation (in degrees).
 * @param duration The time it takes for the robot to turn (in ms).
 */
void dt_turn(double angle, int duration);

/**
 * Turns the drivetrain towards a point (x, y) for a duration of time.
 * 
 * @param x, y The coordinates of the point.
 * @param duration The time it takes for the robot to turn (in ms).
 */
void dt_turn(double x, double y, int duration);

/**
 * Moves the drivetrain in a straight line for a given distance and duration of time.
 * 
 * @param distance The distance  from the robot's original position (in inches).
 * @param duration The time it takes for the robot to move (in ms).
 */
void dt_move_straight(double distance, int duration);

/**
 * Moves the drivetrain towards a point (x, y) for a duration of time.
 * The robot stops at the closest distance given.
 * 
 * @param x, y The coordinates of the point.
 * @param turn_duration The time it takes for the robot to turn (in ms).
 * @param move_duration The time it takes for the robot to move (in ms).
 * @param end_distance The distance the robot stops at before reaching the point (in inches).
 */
void dt_move_straight(double x, double y, int turn_duration, int move_duration, double end_distance);

#endif
