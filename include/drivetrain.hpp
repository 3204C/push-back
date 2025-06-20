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
void drivetrain_driver_control(int left_voltage, int right_voltage, int min_voltage);

#endif
