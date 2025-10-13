// TODO: Add file description
/**
 * @file main.cpp
 * 
 * This is the entry point of the robot.
 */

#include "main.h"
#include "autonomous.hpp"
#include "drivetrain.hpp"
#include "intake.hpp"
#include "conveyor.hpp"

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
    // positios to 0 degrees.
	dt_left.set_brake_mode_all(MOTOR_BRAKE_BRAKE);
	dt_left.set_encoder_units_all(MOTOR_ENCODER_DEGREES);
	dt_left.tare_position_all();
	dt_right.set_brake_mode_all(MOTOR_BRAKE_BRAKE);
	dt_right.set_encoder_units_all(MOTOR_ENCODER_DEGREES);
	dt_right.tare_position_all();

    // Set the intake motors' brake mode and encoder units, then reset their
    // positions to 0 degrees.
    intake.set_brake_mode_all(MOTOR_BRAKE_HOLD);
	intake.set_encoder_units_all(MOTOR_ENCODER_DEGREES);
	intake.tare_position_all();

    // Set the conveyor belt motors' brake mode and encoder units, then reset their
    // positions to 0 degrees.
    conveyor.set_brake_mode_all(MOTOR_BRAKE_HOLD);
	conveyor.set_encoder_units_all(MOTOR_ENCODER_DEGREES);
	conveyor.tare_position_all();

    // Create a task to run the debugger asynchronously.
    // pros::Task debugger(debug);

    auton_routine = 0;

    pros::lcd::set_text(1, "Autonomous routine selected: none");
    pros::lcd::register_btn0_cb(auton_select_left);
    pros::lcd::register_btn1_cb(auton_select_none);
    pros::lcd::register_btn2_cb(auton_select_right);
}

void disabled() {}

void competition_initialize() {}

void autonomous()
{
    pros::lcd::set_text(2, "Autonomous start");

    auton_routine = 0;

    // Left side autonomous routine
    if (auton_routine == 1)
    {
        // Spin the intake inwards to pick up blocks.
        intake_spin(1, 0);

        // Move towards the centre blocks.
        dt_move_straight(44.0, 2000);

        // Stop the intake.
        intake_spin(0, 0);

        // Turn towards the centre goal.
        dt_turn(45.0, 1000);

        // Move towards the centre goal.
        dt_move_straight(9.0, 1000);

        intake_spin(0, 1, 1500);
    }

    // Right side autonomous routine
    else if (auton_routine == 2)
    {
        // Spin the intake inwards to pick up blocks.
        intake_spin(1, 0);

        // Move towards the centre blocks.
        dt_move_straight(44.0, 1500);

        // Stop the intake.
        intake_spin(0, 0);

        // Turn towards the centre goal.
        dt_turn(-45.0, 1000);

        // Move towards the centre goal.
        dt_move_straight(9.0, 1000);

        intake_spin(0, 1, 1500);
    }
}

void opcontrol()
{
    pros::lcd::set_text(3, "Driver control start");

    // Repeat until driver control is over.
	while (true)
	{
        // Control the drivetrain using voltage from the joysticks with a mininum
        // voltage of 4 V. The left joystick controls the left side, and the right
        // joystick controls the right side.
		dt_move_voltage(controller.get_analog(ANALOG_LEFT_Y),
            controller.get_analog(ANALOG_RIGHT_Y), 4);

        // Spin the intake using the controller. Pressing R1 spins the intake inward,
        // and pressing R2 spins the intake outward. Pressing both or neither will not
        // make the intake spin.
        intake_spin(controller.get_digital(DIGITAL_R1),
            controller.get_digital(DIGITAL_R2));

        // Spin the conveyor belt using the controller. Pressing L1 spins the conveyor
        // belt upward, and pressing L2 spins the conveyor belt downward. Pressing both
        // or neither will not make the conveyor belt spin.
        conveyor_spin(controller.get_digital(DIGITAL_L1),
            controller.get_digital(DIGITAL_L2));

		pros::delay(20);
	}
}
