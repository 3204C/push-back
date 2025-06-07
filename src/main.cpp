// TODO: Add file description
/**
 * @file main.cpp
 * 
 * [description]
 */


#include "main.h"
#include "drivetrain.hpp"


void debug()
{
    while (true)
    {
        pros::lcd::set_text(5, std::format("X-position: {:.2f}", gps.get_position_x()));
        pros::lcd::set_text(6, std::format("Y-position: {:.2f}", gps.get_position_y()));
        pros::lcd::set_text(7, std::format("Heading: {:.2f}", gps.get_heading()));

        pros::delay(100);
    }
}


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

    // Create a task to run the debugger.
    pros::Task debugger(debug);
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
