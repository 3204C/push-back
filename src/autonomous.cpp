/**
 * @file autonomous.cpp
 * 
 * [description]
 */

#include "main.h"
#include "autonomous.hpp"

int auton_routine = 0;

void auton_select_none()
{
    pros::lcd::print(1, "Autonomous routine selected: none");
    auton_routine = 0;
}

void auton_select_left()
{   
    pros::lcd::print(1, "Autonomous routine selected: left");
    auton_routine = 1;
}

void auton_select_right()
{   
    pros::lcd::print(1, "Autonomous routine selected: right");
    auton_routine = 2;
}
