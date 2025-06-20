// TODO: Add file description
/**
 * @file main.cpp
 * 
 * This is the main program of the robot. All 
 */

#include "main.h"
#include "drivetrain.hpp"
#include "intake.hpp"

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
    // position to 0 degrees.
	drivetrain_left.set_brake_mode_all(MOTOR_BRAKE_BRAKE);
	drivetrain_left.set_encoder_units_all(MOTOR_ENCODER_DEGREES);
	drivetrain_left.tare_position_all();
	drivetrain_right.set_brake_mode_all(MOTOR_BRAKE_BRAKE);
	drivetrain_right.set_encoder_units_all(MOTOR_ENCODER_DEGREES);
	drivetrain_right.tare_position_all();

    // Set the intake motor's brake mode and encoder units, then reset its
    // position to 0 degrees.
    intake.set_brake_mode(MOTOR_BRAKE_BRAKE);
	intake.set_encoder_units(MOTOR_ENCODER_DEGREES);
	intake.tare_position();

    // Create a task to run the debugger asynchronously.
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
        // Control the drivetrain using voltage from the joysticks with a mininum
        // voltage of 4 V. The left joystick controls the left side, and the right
        // joystick controls the right side.
		drivetrain_driver_control(controller.get_analog(ANALOG_LEFT_Y),
            controller.get_analog(ANALOG_RIGHT_Y), 4);

        // Spin the intake using the controller. Pressing R1 spins the intake inwards,
        // and pressing R2 spins the intake outwards. Pressing both or neither will not
        // make the intake spin.
        intake_spin(controller.get_digital(DIGITAL_R1),
            controller.get_digital(DIGITAL_R2));

		pros::delay(20);
	}
}
