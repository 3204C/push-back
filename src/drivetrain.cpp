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


void drivetrain_driver_control(int voltage_left, int voltage_right, double deadzone)
{
    // Left side motors are controlled with the left joystick.
    // Only spin the motors when the left stick is past the deadzone.
    if (voltage_left < (deadzone * -1) or voltage_left > deadzone)
    {
        /**
         * The range of the voltage was originally d <= V <= 127; the minimum is the
         * deadzone (d) and the maximum is 127 V. This means that once the joystick
         * goes past the deadzone, the drivetrain immediately has speed. To make it
         * smoother, the range is changed to 0 <= V <= 127 so the robot starts at 0 V
         * when the joystick goes past the deadzone. The calculation for the equation
         * is below:
         * 
         * d <= V <= 127 (original)
         * 0 <= V - d <= 127 - d (subtract d)
         * 0 <= (V - d) / (127 - d) <= 1 (divide by 127 - d)
         * 0 <= 127 * (V - d) / (127 - d) <= 127 (multiply by 127)
         */
        drivetrain_left.move((voltage_left - deadzone) * 127 / (127 - deadzone));
    }
    else
    {
        // Stop the motors when the joystick is inside the deadzone.
        drivetrain_left.brake();
    }

    // Right side motors are controlled with the right joystick.
    // Only spin the motors when the right stick is past the deadzone.
    if (voltage_right < (deadzone * -1) or voltage_right > deadzone)
    {
        // (read explanation above)
        drivetrain_right.move((voltage_right - deadzone) * 100 / (100 - deadzone));
    }
    else
    {
        // Stop the motors when the joystick is inside the deadzone.
        drivetrain_right.brake();
    }
}
