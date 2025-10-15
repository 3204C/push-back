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

/// The distance between the two wheels on each side (in inches).
#define TRACK_WIDTH 15

/// The distance between the two end wheels on the same side (in inches).
#define WHEELBASE 10

/// Pi to 7 significant figures.
#define PI 3.141593

double degrees_to_radians(double angle)
{
    return angle / 180 * PI;
}

double radians_to_degrees(double angle)
{
    return angle * 180 / PI;
}

double radians_to_revolutions(double angle)
{
    return angle / (2 * PI);
}

double distance_to_point(double x, double y)
{
    // Calculate the x and y component distances.
    double delta_x = x - gps.get_position_x();
    double delta_y = y - gps.get_position_y();

    // Calculate the absolute distance using the Pythagorean theorem.
    double distance = std::sqrt(delta_x * delta_x + delta_y + delta_y);

    // Convert the distance from metres to inches.
    distance *= 39.37;

    return distance;
}

double heading_from_robot(double x, double y)
{
    // Calculate the x and y component distances.
    double delta_x = x - gps.get_position_x();
    double delta_y = y - gps.get_position_y();

    // Calculate the angle using the arctangent function.
    double heading = std::atan2(delta_y, delta_x);

    // Convert the angle from radians to degrees.
    heading = radians_to_degrees(heading);

    // If the angle is negative, add 360 degrees to turn it positive.
    if (heading < 0) { heading += 360; }

    // Turn the angle into a heading.
    heading = 90 - heading;

    return heading;
}

double angle_from_robot(double x, double y)
{
    double heading = heading_from_robot(x, y);

    // Calculate the two possible angles the robot can turn to face the point.
    double angle_1 = heading - gps.get_heading();
    double angle_2 = 360 - angle_1;

    // Return the smaller angle between the two.
    return std::max(angle_1, angle_2);
}

void dt_move_voltage(int left_voltage, int right_voltage, int min_voltage)
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

void dt_move_voltage(int left_voltage, int right_voltage, int min_voltage, int duration)
{
    // Spin the motors with the specified values.
    dt_move_voltage(left_voltage, right_voltage, min_voltage);
    
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
     * d (in) = R (in) * THETA (rad)                        (displacement of wheel)
     * v (in/min) = d (in) / t (ms) * 60000 (ms/min)        (velocity of wheel)
     * v (in/min) = r (in) * omega (rad/min)                
     * omega (rad/min) = v (in/min) / r (in)                (angular velocity of motor)
     * omega (rev/min) = omega (rad/min) / (2 * pi)         (convert to revolutions per min)
     */
    
    double radians = degrees_to_radians(angle);

    double turning_radius_centre = TRACK_WIDTH / 2;
    double distance_centre = turning_radius_centre * abs(radians);
    double velocity_centre = distance_centre / duration * 60000;
    double angular_velocity_centre = velocity_centre / WHEEL_RADIUS;
    angular_velocity_centre = radians_to_revolutions(angular_velocity_centre);

    double turning_radius_far = sqrt(WHEELBASE * WHEELBASE + TRACK_WIDTH * TRACK_WIDTH) / 2;
    double distance_far = turning_radius_far * abs(radians);
    double velocity_far = distance_far / duration * 60000;
    double angular_velocity_far = velocity_far / WHEEL_RADIUS;
    angular_velocity_far = radians_to_revolutions(angular_velocity_far);

    // Determine the direction of rotation, then spin the motors as desired.
    if (angle > 0)
    {
        dt_left_front.move_velocity(angular_velocity_far);
        dt_left_centre.move_velocity(angular_velocity_centre);
        dt_left_back.move_velocity(angular_velocity_far);

        dt_right_front.move_velocity(-angular_velocity_far);
        dt_right_centre.move_velocity(-angular_velocity_centre);
        dt_right_back.move_velocity(-angular_velocity_far);
    }
    else if (angle < 0)
    {
        dt_left_front.move_velocity(-angular_velocity_far);
        dt_left_centre.move_velocity(-angular_velocity_centre);
        dt_left_back.move_velocity(-angular_velocity_far);

        dt_right_front.move_velocity(angular_velocity_far);
        dt_right_centre.move_velocity(angular_velocity_centre);
        dt_right_back.move_velocity(angular_velocity_far);
    }
    
    // The drivetrain will stop after the set duration has passed.
    pros::delay(duration);
    dt_left.brake();
    dt_right.brake();
}

void dt_turn(double x, double y, int duration)
{
    // Calculate the smallest angle that the robot can turn to face the point.
    double angle = angle_from_robot(x, y);

    // Turn towards the point.
    dt_turn(angle, duration);
}

void dt_move_straight(double distance, int duration)
{
    /**
     * Calculate the angular velocity of each motor using the formulas below:
     * 
     * v (in/min) = d (in) / t (ms) * 60000 (ms/min)    (velocity of wheel)
     * v (in/min) = r (in) * omega (rad/min)
     * omega (rad/min) = v (in/min) / r (in)            (angular velocity of motor)
     * omega (rev/min) = omega (rad/min) / (2 * pi)     (convert to revolutions per min)
     */
    double velocity = distance / duration * 60000;
    double angular_velocity = velocity / WHEEL_RADIUS;
    angular_velocity = radians_to_revolutions(angular_velocity);

    // Spin the motors with the calculated angular velocity.
    dt_left.move_velocity(angular_velocity);
    dt_right.move_velocity(angular_velocity);

    // The drivetrain will stop after the set duration has passed.
    pros::delay(duration);
    dt_left.brake();
    dt_right.brake();
}

void dt_move_straight(double x, double y, int turn_duration, int move_duration, double end_distance)
{   
    // Calculate the distance between the robot and the given point.
    double distance = distance_to_point(x, y);

    // Reduce the travel distance so the robot stops at a given end distance.
    distance -= end_distance;

    // Turn towards the point.
    dt_turn(x, y, turn_duration);

    // Move towards the point.
    dt_move_straight(distance, move_duration);
}
