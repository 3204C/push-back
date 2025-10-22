/**
 * @file intake.cpp
 * 
 * This file defines all variables and functions declared in "intake.hpp".
 * All variables and functions defined here are for the intake's
 * autonomous and driver control movement.
 */

#include "main.h"
#include "intake.hpp"

void intake_spin(int is_inward, int is_outward, int voltage)
{   
    // Calculate the net direction.
    int direction = is_inward - is_outward;

    // If no direction is given, nothing happens.
    if (direction == 0)
    {
        intake.brake();
    }

    // The intake spins inward if the direction is positive and spins outward
    // if the direction is negative.
    else
    {
        intake.move(voltage * direction);
    }
}

void intake_spin(int is_inward, int is_outward, int voltage, int duration)
{   
    // Spin the intake according to the direction given.
    intake_spin(is_inward, is_outward, voltage);

    // The intake will stop after the set duration has passed.
    pros::delay(duration);
    intake.brake();
}
