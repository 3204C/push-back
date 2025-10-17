/**
 * @file conveyor.cpp
 * 
 * This file defines all variables and functions declared in "conveyor.hpp".
 * All variables and functions defined here are for the conveyor belt's
 * autonomous and driver control movement.
 */

#include "main.h"
#include "conveyor.hpp"

// The voltage of the conveyor belt motor when spinning.
#define CONVEYOR_VOLTAGE 127

void conveyor_spin(int is_upward, int is_downward)
{   
    // Calculate the net direction.
    int direction = is_upward - is_downward;

    // If no direction is given, nothing happens.
    if (direction == 0)
    {
        conveyor.brake();
    }

    // The conveyor belt spins upward if the direction is positive and spins
    // downward if the direction is negative.
    else
    {
        conveyor.move(CONVEYOR_VOLTAGE * direction);
    }
}

void conveyor_spin(int is_upward, int is_downward, int duration)
{   
    // Spin the conveyor belt according to the direction given.
    conveyor_spin(is_upward, is_downward);

    // The conveyor belt will stop after the set duration has passed.
    pros::delay(duration);
    conveyor.brake();
}
