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

/// The maximum voltage each motor can take.
#define MAX_DT_VOLTAGE 127

/// The radius of each drivetrain wheel (in inches).
#define WHEEL_RADIUS 2

/// The distance between the two wheels on each side.
#define TRACK_WIDTH 15

void dt_move(int left_voltage, int right_voltage, int min_voltage)
{
    // Spin the left side motors when the size of the left side's voltage is
    // greater than the minimum required voltage.
    if (abs(left_voltage) > min_voltage)
    {
        /**
         * The range of the input voltage is changed from min <= V <= 127 to
         * 0 <= 127 * (V - min) / (127 - min) <= 127 using the calculations below:
         * 
         * 4 <= V <= 127
         * 0 <= V - min <= 127 - min                    (subtract d)
         * 0 <= (V - min) / (127 - min) <= 1            (divide by 127 - 4)
         * 0 <= 127 * (V - min) / (127 - min) <= 127    (multiply by 127)
         */
        dt_left.move((left_voltage - min_voltage) * MAX_DT_VOLTAGE / 
            (MAX_DT_VOLTAGE - min_voltage));
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
        dt_right.move((right_voltage - min_voltage) * MAX_DT_VOLTAGE / 
            (MAX_DT_VOLTAGE - min_voltage));
    }
    else
    {
        // Stop the motors when the input voltage is below the minimum.
        dt_right.brake();
    }
}

void dt_move(int left_voltage, int right_voltage, int min_voltage, int duration)
{
    // Spin the motors with the specified values.
    dt_move(left_voltage, right_voltage, min_voltage);
    
    // The drivetrain will stop after the set duration has passed.
    pros::delay(duration);
    dt_left.brake();
    dt_right.brake();
}

void dt_move_straight(double distance, int duration)
{
    /**
     * Calculate the angular velocity of each motor using the formulas below:
     * 
     * v (in/min) = d (in) / t (ms) * 60000 (ms/min)    (velocity of wheel)
     * v (in/min) = r (in) * omega (rot/min)
     * omega (rot/min) = v (in/min) / r (in)            (angular velocity of motor)
     */
    double velocity = distance / duration * 60000;
    double angular_velocity = velocity / WHEEL_RADIUS;

    // Spin the motors with the calculated angular velocity.
    dt_left.move_velocity(angular_velocity);
    dt_right.move_velocity(angular_velocity);

    // The drivetrain will stop after the set duration has passed.
    pros::delay(duration);
    dt_left.brake();
    dt_right.brake();
}

void dt_turn(double angle, int duration)
{
    /**
     * Calculate the angular velocity of each motor using the formulas below:
     * 
     * R (in) = 1/2 * sqrt([wheelbase]^2 + [track width]^2) (radius of turning circle)
     * d (in) = R (in) * THETA (deg) / 360 (deg)            (displacement of wheel)
     * v (in/min) = d (in) / t (ms) * 60000 (ms/min)        (velocity of wheel)
     * v (in/min) = r (in) * omega (rot/min)                
     * omega (rot/min) = v (in/min) / r (in)                (angular velocity of motor)
     */
    double turning_radius = TRACK_WIDTH / 2;
    double distance = turning_radius * abs(angle) / 360;
    double velocity = distance / duration * 60000;
    double angular_velocity = velocity / WHEEL_RADIUS;

    // Determine the direction of rotation, then spin the motors as desired.
    if (angle > 0)
    {
        dt_left.move_velocity(angular_velocity);
        dt_right.move_velocity(-angular_velocity);
    }
    else if (angle < 0)
    {
        dt_left.move_velocity(-angular_velocity);
        dt_right.move_velocity(angular_velocity);
    }
    
    // The drivetrain will stop after the set duration has passed.
    pros::delay(duration);
    dt_left.brake();
    dt_right.brake();
}
