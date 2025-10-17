/**
 * @file outtake.cpp
 * 
 * This file defines all variables and functions declared in "outtake.hpp".
 * All variables and functions defined here are for the outtake's
 * autonomous and driver control movement.
 */

#include "main.h"
#include "outtake.hpp"

// The voltage of the outtake motor when spinning.
#define OUTTAKE_VOLTAGE 127

void outtake_spin(int is_outward, int is_inward)
{   
    // Calculate the net direction.
    int direction = is_outward - is_inward;

    // If no direction is given, nothing happens.
    if (direction == 0)
    {
        outtake.brake();
    }

    // The outtake spins inward if the direction is positive and spins outward
    // if the direction is negative.
    else
    {
        outtake.move(OUTTAKE_VOLTAGE * direction);
    }
}

void outtake_spin(int is_outward, int is_inward, int duration)
{   
    // Spin the outtake according to the direction given.
    outtake_spin(is_outward, is_inward);

    // The outtake will stop after the set duration has passed.
    pros::delay(duration);
    outtake.brake();
}
