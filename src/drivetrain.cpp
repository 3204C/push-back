/**
 * @file drivetrain.cpp
 * 
 * This file defines all variables and functions declared in "drivetrain.hpp".
 * All variables and functions defined here are for the drivetrain's
 * autonomous and driver control movement. Some functions utilise the VEX V5
 * GPS Sensor to identify the robot's position and heading on the field.
 */

#include "main.h"
#include "drivetrain.hpp"
#include <cmath>

/// The radius of each drivetrain wheel (in inches).
#define WHEEL_RADIUS 2

/// The circumference of each drivetrain wheel (in inches, rounded to 7 sf).
#define WHEEL_CIRCUMFERENCE 12.56637

/// The distance between the two wheels on each side (in inches).
#define TRACK_WIDTH 15

/// The distance between the two end wheels on the same side (in inches).
#define WHEELBASE 10

/// Pi to 7 significant figures.
#define PI 3.141593

// double distance_to_point(double x, double y)
// {
//     // Calculate the x and y component distances.
//     double delta_x = x - gps.get_position_x();
//     double delta_y = y - gps.get_position_y();

//     // Calculate the absolute distance using the Pythagorean theorem.
//     double distance = std::sqrt(delta_x * delta_x + delta_y * delta_y);

//     // Convert the distance from metres to inches.
//     distance *= 39.37;

//     return distance;
// }

// double heading_from_robot(double x, double y)
// {
//     // Calculate the x and y component distances.
//     double delta_x = x - gps.get_position_x();
//     double delta_y = y - gps.get_position_y();

//     // Calculate the angle using the arctangent function.
//     double heading = std::atan2(delta_y, delta_x);

//     // Convert the angle from radians to degrees.
//     heading * 180 / PI;

//     // If the angle is negative, add 360 degrees to turn it positive.
//     if (heading < 0) { heading += 360; }

//     // Turn the angle into a heading.
//     heading = 90 - heading;

//     return heading;
// }

// double angle_from_robot(double x, double y)
// {
//     double heading = heading_from_robot(x, y);

//     // Calculate the two possible angles the robot can turn to face the point.
//     double angle_1 = heading - gps.get_heading();
//     double angle_2 = 360 - angle_1;

//     // Return the smaller angle between the two.
//     return std::max(angle_1, angle_2);
// }

void dt_move_voltage(int left_voltage, int right_voltage, int min_voltage,
    int max_voltage)
{
    // Spin the left side motors when the size of the left side's voltage is
    // greater than the minimum required voltage.
    if (abs(left_voltage) > min_voltage)
    {
        /**
         * The range of the input voltage is changed from min <= V <= max to
         * 0 <= max * (V - min) / (max - min) <= max using the calculations below:
         * 
         * min <= V <= max
         * 0 <= V - min <= max - min                    (subtract min)
         * 0 <= (V - min) / (max - min) <= 1            (divide by max - min)
         * 0 <= max * (V - min) / (max - min) <= max    (multiply by max)
         */
        dt_left.move((left_voltage - min_voltage) * max_voltage / 
            (max_voltage - min_voltage));
    }
    else
    {
        // Stop the motors when the input voltage is below the minimum.
        dt_left.brake();
    }

    // Spin the right side motors when the size of the right side's voltage is
    // greater than the minimum required voltage.
    if (abs(right_voltage) > min_voltage)
    {
        dt_right.move((right_voltage - min_voltage) * max_voltage / 
            (max_voltage - min_voltage));
    }
    else
    {
        // Stop the motors when the input voltage is below the minimum.
        dt_right.brake();
    }
}

void dt_move_voltage(int left_voltage, int right_voltage, int min_voltage,
    int max_voltage, int duration)
{
    // Spin the motors with the specified values.
    dt_move_voltage(left_voltage, right_voltage, min_voltage, max_voltage);
    
    // The drivetrain will stop after the set duration has passed.
    pros::delay(duration);
    dt_left.brake();
    dt_right.brake();
}

void dt_turn(double angle, int duration, bool is_blocking)
{
    /**
     * Calculate the revolutions each motor makes.
     * 
     * turning radius (R) = 7.5 in
     * wheel circumference (c) = 12.56637 in (7 sf)
     * turning angle (theta) = [angle]
     * 
     * turning circumference (C) = 2 * pi * R
     * distance (d) = C * theta / 360
     * revolutions = d / c
     */
    double turning_radius = TRACK_WIDTH / 2;
    double turning_circumference = turning_radius * 2 * PI;
    double distance = turning_circumference * angle / 360;
    double revolutions = distance / WHEEL_CIRCUMFERENCE;

    /**
     * Calculate the angular velocity of each motor.
     * 
     * distance (d) = C * theta / 360
     * time (t) = [duration]
     * wheel radius (r) = 2 in
     * 
     * velocity (v) = d / t * 60000
     * angular velocity (omega) = (v / r) / (2 * pi)
     */
    double velocity = distance / duration * 60000;
    double angular_velocity = velocity / WHEEL_RADIUS;
    angular_velocity /= 2 * PI;

    // Spin the motors.
    dt_left.move_relative(revolutions, angular_velocity);
    dt_right.move_relative(-revolutions, angular_velocity);

    // If blocking is enabled, wait for the motors to finish spinning.
    if (is_blocking)
    {
        pros::delay(duration + 50);
    }
}

// void dt_turn(double x, double y, int duration, bool is_blocking)
// {
//     // Calculate the smallest angle that the robot can turn to face the point.
//     double angle = angle_from_robot(x, y);

//     // Turn towards the point.
//     dt_turn(angle, duration, is_blocking);
// }

void dt_move_straight(double distance, int duration, bool is_blocking)
{
    /**
     * Calculate the revolutions each motor makes.
     * 
     * distance (d) = [distance]
     * wheel circumference (c) = 12.56637 in (7 sf)
     * 
     * revolutions = d / c
     */
    double revolutions = distance / WHEEL_CIRCUMFERENCE;
    
    /**
     * Calculate the angular velocity of each motor.
     * 
     * distance (d) = [distance]
     * time (t) = [duration]
     * wheel radius (r) = 2 in
     * 
     * velocity (v) = d / t * 60000
     * angular velocity (omega) = (v / r) / (2 * pi)
     */
    double velocity = distance / duration * 60000;
    double angular_velocity = velocity / WHEEL_RADIUS;
    angular_velocity /= 2 * PI;

    // Spin the motors.
    dt_left.move_relative(revolutions, angular_velocity);
    dt_right.move_relative(revolutions, angular_velocity);

    // If blocking is enabled, wait for the motors to finish spinning.
    if (is_blocking)
    {
        pros::delay(duration + 50);
    }
}

// void dt_move_straight(double x, double y, int turn_duration, int move_duration,
//     double end_distance, bool is_blocking)
// {   
//     // Calculate the distance between the robot and the given point.
//     double distance = distance_to_point(x, y);

//     // Reduce the travel distance so the robot stops at a given end distance.
//     distance -= end_distance;

//     // Turn towards the point.
//     dt_turn(x, y, turn_duration, true);

//     // Move towards the point.
//     dt_move_straight(distance, move_duration, is_blocking);
// }
