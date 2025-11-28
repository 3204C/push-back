// TODO: Add file description
/**
 * @file main.cpp
 * 
 * This is the entry point of the robot.
 */

#include "main.h"
#include "drivetrain.hpp"
#include "intake.hpp"
#include "conveyor.hpp"
#include "outtake.hpp"

/// The number of the routine the robot is set to perform.
int routine;

// void debug()
// {
//     pros::lcd::set_text(5, std::format("X-position: {:.2f}", gps.get_position_x()));
//     pros::lcd::set_text(6, std::format("Y-position: {:.2f}", gps.get_position_y()));
//     pros::lcd::set_text(7, std::format("Heading: {:.2f}", gps.get_heading()));
// }

void routine_auton_left()
{
    // Set the routine to driver control after finishing.
    routine = 0;
}

void routine_auton_right()
{
    // Set the outtake pneumatics to the upward position.
    pneumatics.set_value(0);

    // Spin the intake inwards to pick up blocks.
    intake_spin(1, 0, 127);

    // Move towards the centre blocks.
    dt_move_straight(42.0, 2500, true);

    // Stop the intake.
    intake_spin(0, 0, 127);

    // Turn towards the centre goal.
    dt_turn(-45.0, 1000, true);

    // Move towards the centre goal.
    dt_move_straight(6.0, 1000, true);

    // Spin the intake outwards to let go of the block.
    intake_spin(0, 1, 127, 2000);

    // Spin the conveyor downwards.
    conveyor_spin(0, 1, 127, 2000);

    // Spin the intake outwards to let go of the block.
    intake_spin(0, 1, 127, 2000);

    // Move towards the centre goal.
    dt_move_straight(3.0, 1000, true);

    // Set the routine to driver control after finishing.
    routine = 0;
}

void routine_driver_control()
{
    // Control the drivetrain using voltage from the joysticks. The left joystick
    // controls the left side, and the right joystick controls the right side.
    if (controller.get_digital(DIGITAL_A))
    {
        dt_move_voltage(controller.get_analog(ANALOG_RIGHT_Y) * -1,
            controller.get_analog(ANALOG_LEFT_Y) * -1, 4, 127);
    }
    else
    {
        dt_move_voltage(controller.get_analog(ANALOG_LEFT_Y),
            controller.get_analog(ANALOG_RIGHT_Y), 4, 127);
    }
    
    // Spin the intake using the controller. Pressing L1 spins the intake inward,
    // and pressing L2 spins the intake outward. Pressing both or neither will not
    // make the intake spin.
    intake_spin(controller.get_digital(DIGITAL_R1),
        controller.get_digital(DIGITAL_R2), 127);

    // Spin the conveyor belt using the controller. Pressing L1 spins the conveyor
    // belt upward, and pressing L2 spins the conveyor belt downward. Pressing both
    // or neither will not make the conveyor belt spin.
    conveyor_spin(controller.get_digital(DIGITAL_R1),
        controller.get_digital(DIGITAL_R2), 127);
    
    // Spin the outtake using the controller. Pressing R1 spins the outtake outward,
    // and pressing R2 spins the outtake inward. Pressing both or neither will not
    // make the outtake spin.
    outtake_spin(controller.get_digital(DIGITAL_L1),
        controller.get_digital(DIGITAL_L2), 31);

    // Lift the outtake using the controller. Pressing the up arrow lifts the outtake
    // upward, and pressing the down arrow lifts the outtake downward. Pressing both
    // or neither will not make the outtake lift.
    outtake_lift(controller.get_digital(DIGITAL_UP),
        controller.get_digital(DIGITAL_DOWN));
}

void initialize()
{
    // Initialise the Brain screen.
    pros::lcd::initialize();

	pros::lcd::set_text(0, "Starting initialisation...");

    // Set the drivetrain motors' brake mode and encoder units, then reset their
    // positions to 0 rotations.
	dt_left.set_brake_mode_all(MOTOR_BRAKE_BRAKE);
	dt_left.set_encoder_units_all(MOTOR_ENCODER_ROTATIONS);
	dt_left.tare_position_all();
	dt_right.set_brake_mode_all(MOTOR_BRAKE_BRAKE);
	dt_right.set_encoder_units_all(MOTOR_ENCODER_ROTATIONS);
	dt_right.tare_position_all();

    // Set the intake motors' brake mode and encoder units, then reset their
    // positions to 0 rotations.
    intake.set_brake_mode_all(MOTOR_BRAKE_HOLD);
	intake.set_encoder_units_all(MOTOR_ENCODER_ROTATIONS);
	intake.tare_position_all();

    // Set the conveyor belt motor's brake mode and encoder units, then reset its
    // position to 0 rotations.
    conveyor.set_brake_mode(MOTOR_BRAKE_HOLD);
	conveyor.set_encoder_units(MOTOR_ENCODER_ROTATIONS);
	conveyor.tare_position();

    // Set the outtake motor's brake mode and encoder units, then reset its
    // position to 0 rotations.
    outtake.set_brake_mode_all(MOTOR_BRAKE_HOLD);
	outtake.set_encoder_units_all(MOTOR_ENCODER_ROTATIONS);
	outtake.tare_position_all();

    // Set up the routine selection.
    routine = 0;
    pros::lcd::set_text(1, "Routine: none/driver control");
    controller.set_text(0, 0, "Routine: none/driver");

    // Routine selection with brain buttons
    pros::lcd::register_btn0_cb([]()
    {
        routine = 0;
        pros::lcd::set_text(1, "Routine: none/driver control");
        controller.set_text(0, 0, "Routine: none/driver");
    });

    // pros::lcd::register_btn1_cb([]()
    // {
    //     routine = 1;
    //     pros::lcd::set_text(1, "Routine: left side autonomous");
    //     controller.set_text(0, 0, "Routine: left auton");
    // });

    pros::lcd::register_btn2_cb([]()
    {
        routine = 2;
        pros::lcd::set_text(1, "Routine: right side autonomous");
        controller.set_text(0, 0, "Routine: right auton");
    });

    // // Routine selection with controller buttons
    // if (controller.get_digital(DIGITAL_X))
    // {
    //     routine = 0;
    //     pros::lcd::set_text(1, "Routine: none/driver control");
    //     controller.set_text(0, 0, "Routine: none/driver");
    // }

    // else if (controller.get_digital(DIGITAL_Y))
    // {
    //     routine = 1;
    //     pros::lcd::set_text(1, "Routine: left side autonomous");
    //     controller.set_text(0, 0, "Routine: left auton");
    // }

    // else if (controller.get_digital(DIGITAL_B))
    // {
    //     routine = 2;
    //     pros::lcd::set_text(1, "Routine: right side autonomous");
    //     controller.set_text(0, 0, "Routine: right auton");
    // }
}

void disabled() {}

void competition_initialize() {}

void autonomous()
{
    pros::lcd::set_text(0, "Starting autonomous...");

    // Left side autonomous routine
    if (routine == 1) { routine_auton_left(); }

    // Right side autonomous routine
    else if (routine == 2) { routine_auton_right(); }
}

void opcontrol()
{
    pros::lcd::set_text(0, "Starting driver control...");

    // Repeat until driver control is over.
	while (true)
	{
        // Driver control routine
        if (routine == 0) { routine_driver_control(); }

        // // Left side autonomous routine
        // else if (routine == 1) { routine_auton_left(); }

        // Right side autonomous routine
        else if (routine == 2) { routine_auton_right(); }
        
        // // Run the debugger on the Brain screen.
        // debug();

        pros::delay(100);
	}
}
