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
 * @param voltage_left The voltage of each motor on the left side of the drivetrain.
 * @param voltage_right The voltage of each motor on the right side of the drivetrain.
 * @param deadzone The minimum voltage required to spin the motors.
 */
void drivetrain_driver_control(int voltage_left, int voltage_right, double deadzone);


#endif
