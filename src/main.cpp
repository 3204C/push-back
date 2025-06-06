/**
 * @file main.cpp
 * 
 * [description]
 */
// TODO: Add file description


#include "main.h"
#include "drivetrain.hpp"


void initialize()
{
    // Initialise the Brain screen.
    pros::lcd::initialize();

	pros::lcd::set_text(0, "Program start");

    // Set the drivetrain motors' brake mode and encoder units, then reset their
    // position to 0 deg.
	drivetrain_left.set_brake_mode_all(MOTOR_BRAKE_BRAKE);
	drivetrain_left.set_encoder_units_all(MOTOR_ENCODER_DEGREES);
	drivetrain_left.tare_position_all();
	drivetrain_right.set_brake_mode_all(MOTOR_BRAKE_BRAKE);
	drivetrain_right.set_encoder_units_all(MOTOR_ENCODER_DEGREES);
	drivetrain_right.tare_position_all();
}


void disabled() {}


void competition_initialize() {}


void autonomous()
{
    pros::lcd::set_text(1, "Autonomous start");
}


void opcontrol()
{
    pros::lcd::set_text(2, "Driver control start");

    // Repeat until driver control is over.
	while (true)
	{
        // Control the drivetrain using voltage from the joysticks.
		drivetrain_driver_control(controller.get_analog(ANALOG_LEFT_Y), controller.get_analog(ANALOG_RIGHT_Y));

		pros::delay(20);
	}
}
