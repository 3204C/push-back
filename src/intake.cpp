/**
 * @file intake.cpp
 * 
 * This file defines all variables and functions declared in "intake.hpp".
 * All variables and functions defined here are for the intake's
 * autonomous and driver control movement.
 */

#include "main.h"
#include "intake.hpp"

// The voltage of the intake motor when spinning.
#define INTAKE_VOLTAGE 127

void intake_spin(int is_intake_pressed, int is_outtake_pressed)
{   
    // Calculate the net direction.
    int direction = is_intake_pressed - is_outtake_pressed;

    // If no direction is given, nothing happens.
    if (direction == 0)
    {
        intake.brake();
    }

    // The intake spins inwards if the direction is positive and spins outwards
    // if the direction is negative.
    else
    {
        intake.move(INTAKE_VOLTAGE * direction);
    }
}

void intake_spin(int is_intake_pressed, int is_outtake_pressed, int duration)
{   
    intake_spin(is_intake_pressed, is_outtake_pressed);

    // The intake will stop after the set duration has passed.
    pros::delay(duration);
    intake.brake();
}
