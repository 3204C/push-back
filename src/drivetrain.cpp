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

// The maximum voltage each motor can take.
#define MAX_DT_VOLTAGE 127

void drivetrain_driver_control(int left_voltage, int right_voltage, int min_voltage)
{
    // Spin the left side motors when the size of the left side's voltage is
    // greater than the minimum required voltage.
    if (abs(left_voltage) > min_voltage)
    {
        /**
         * The range of the voltage is initially m <= V <= 127. This means that between
         * 0 V to m, the voltage is set to 0 V, and once the voltage goes over the
         * minimum, the voltage immediately jumps up to m. To make it smoother, the
         * range is changed to 0 <= V <= 127 so the robot starts at 0 V when the
         * voltage goes over the minimum. The calculation for the equation is below:
         * 
         * m <= V <= 127
         * 0 <= V - m <= 127 - d                  (subtract d)
         * 0 <= (V - m) / (127 - d) <= 1          (divide by 127.0 - d)
         * 0 <= 127 * (V - m) / (127 - d) <= 127  (multiply by 127.0)
         */
        drivetrain_left.move((left_voltage - min_voltage) * MAX_DT_VOLTAGE / 
            (MAX_DT_VOLTAGE - min_voltage));
    }
    else
    {
        // Stop the motors when the input voltage is below the minimum.
        drivetrain_left.brake();
    }

    // Spin the right side motors when the size of the right side's voltage is
    // greater than the minimum required voltage.
    if (abs(right_voltage) > min_voltage)
    {
        drivetrain_right.move((right_voltage - min_voltage) * MAX_DT_VOLTAGE / 
            (MAX_DT_VOLTAGE - min_voltage));
    }
    else
    {
        // Stop the motors when the input voltage is below the minimum.
        drivetrain_right.brake();
    }
}
