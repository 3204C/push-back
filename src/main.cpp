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

// Sensor smoothing variables (0-1).
#define SMOOTHING_GPS_POS 0.4
#define SMOOTHING_GPS_HEADING 0.4
#define SMOOTHING_INERTIAL_HEADING 0.4

/// The direction of the robot's front face.
int direction = 1;

/// The number of the routine the robot is set to perform.
int routine;

/// Location variables.
double gps_pos_x;
double gps_pos_y;
double gps_heading;
double inertial_heading;

void sensors() 
{
    // Smooths raw sensor data.
    gps_pos_x = (SMOOTHING_GPS_POS * gps.get_position_x()) + ((1 - SMOOTHING_GPS_POS) * gps_pos_x);
    gps_pos_y = (SMOOTHING_GPS_POS * gps.get_position_y()) + ((1 - SMOOTHING_GPS_POS) * gps_pos_y);
    gps_heading = (SMOOTHING_GPS_HEADING * gps.get_heading()) + ((1 - SMOOTHING_GPS_HEADING) * gps_heading);
    inertial_heading = (SMOOTHING_INERTIAL_HEADING * inertial.get_heading()) + ((1 - SMOOTHING_INERTIAL_HEADING) * inertial_heading);

    // Prevent out of bound heading values.
    if (inertial_heading >= 360.0 || inertial_heading < 0.0) { inertial_heading = 0.0; }
}

void debug()
{
    pros::lcd::set_text(4, std::format("X-position: {:.2f}", gps_pos_x));
    pros::lcd::set_text(5, std::format("Y-position: {:.2f}", gps_pos_y));
    pros::lcd::set_text(6, std::format("Heading: {:.2f} (GPS), {:.2f} (IMU)", gps_heading, inertial_heading));
    pros::lcd::set_text(7, std::format("Hue: {}", optical.get_hue()));
}

void background_task_fn()
{
    while (true)
    {
        sensors();
        debug();

        pros::delay(100);
    }
}

void routine_auton_test()
{
    dt_turn(360.0, 2000, true);
    dt_move_straight(12.0, 1500, true);
    
    // Set the routine to driver control after finishing.
    pros::lcd::set_text(1, "Routine: none/driver control");
    controller.set_text(0, 0, "Routine: none/driver");
    routine = 0;
}

void routine_auton_left()
{
    // Set the outtake pneumatics to the upward position.
    outtake_lift(1, 0);

    // Spin the intake inwards to pick up blocks.
    intake_spin(1, 0, 127);

    // Move towards the centre blocks.
    dt_move_straight(42.0, 2500, true);

    // Stop the intake.
    intake_spin(0, 0, 127);

    // Turn towards the centre goal.
    dt_turn(45.0, 1000, true);

    // Move towards the centre goal.
    dt_move_straight(6.0, 1000, true);

    // Set the outtake pneumatics to the downward position.
    outtake_lift(0, 1);

    // Wait for 0.5 seconds to ensure the pneumatics have fully lowered.
    pros::delay(500);

    // Spin the outtake outwards to let go of the block.
    outtake_spin(1, 0, 127, 1000);

    // Spin the conveyor upwards.
    conveyor_spin(1, 0, 127, 2000);

    // Spin the outtake outwards to let go of the block.
    outtake_spin(1, 0, 127, 2000);

    // Move towards the centre goal.
    dt_move_straight(3.0, 1000, true);

    // Move away from the centre goal.
    dt_move_straight(-8.0, 1500, true);

    // Set the routine to driver control after finishing.
    pros::lcd::set_text(1, "Routine: none/driver control");
    controller.set_text(0, 0, "Routine: none/driver");
    routine = 0;
}

void routine_auton_right()
{
    // Set the outtake pneumatics to the upward position.
    outtake_lift(1, 0);

    // Spin the intake inwards to pick up blocks.
    intake_spin(1, 0, 127);

    // Move towards the centre blocks.
    dt_move_straight(42.0, 2000, true);

    // Stop the intake.
    intake_spin(0, 0, 0);

    // Turn towards the centre goal.
    dt_turn(-45.0, 500, true);

    // Move towards the centre goal.
    dt_move_straight(5.5, 1000, true);

    // Spin the intake outwards to let go of the first block.
    intake_spin(0, 1, 127);

    // Spin the conveyor downwards.
    conveyor_spin(0, 1, 127, 2000);

    // Stop the intake.
    intake_spin(0, 0, 0);

    // Move away from the centre goal.
    dt_move_straight(-5.0, 1500, true);

    // Move towards the centre goal.
    dt_move_straight(8.0, 1000, true);

    // Move away from the centre goal.
    dt_move_straight(-8.0, 1500, true);

    // Move away from the centre goal.
    dt_move_straight(-8.0, 1500, true);

    // Set the routine to driver control after finishing.
    pros::lcd::set_text(1, "Routine: none/driver control");
    controller.set_text(0, 0, "Routine: none/driver");
    routine = 0;
}

void routine_auton_skills() {}

void routine_driver_control()
{  
    // Control the drivetrain using voltage from the joysticks. The left joystick
    // controls the left side, and the right joystick controls the right side.
    if (direction == 0)
    if (direction == 0)
    {
        dt_move_voltage(controller.get_analog(ANALOG_RIGHT_Y) * -1,
            controller.get_analog(ANALOG_LEFT_Y) * -1, 4, 127);

        // Changes drivetrain direction in driver control.
        if (controller.get_digital(DIGITAL_A)) {
            direction = 1;
            controller.set_text(0, 0, "Front: intake");
        }
    }
    else
    {
        dt_move_voltage(controller.get_analog(ANALOG_LEFT_Y),
            controller.get_analog(ANALOG_RIGHT_Y), 4, 127);

        // Changes drivetrain direction in driver control.
        if (controller.get_digital(DIGITAL_A)) {
            direction = 0;
            controller.set_text(0, 0, "Front: outtake");
        }
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
        controller.get_digital(DIGITAL_L2), 127);
        controller.get_digital(DIGITAL_L2), 127);

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

    // Set the inertial sensor to GPS heading.
    inertial.set_heading(gps.get_heading());
    
    // Set smoothed values to raw values.
    gps_pos_x = gps.get_position_x();
    gps_pos_y = gps.get_position_y();
    gps_heading = gps.get_heading();
    inertial_heading = inertial.get_heading();
    
    // Start the main background task.
    pros::Task background_task(background_task_fn, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "background_task");

    // Wait for GPS values to settle, then set the inertial sensor to GPS heading.
    pros::delay(500);
    inertial.set_heading(gps_heading);

    // Set up the routine selection.
    pros::lcd::set_text(1, "Routine: automatic");
    controller.set_text(0, 0, "Routine: automatic");
    routine = 3;

    // Routine selection with brain buttons
    pros::lcd::register_btn0_cb([]()
    {
        pros::lcd::set_text(1, "Routine: left side autonomous");
        controller.set_text(0, 0, "Routine: left auton");
        routine = 1;
    });
    
    pros::lcd::register_btn1_cb([]()
    {
        pros::lcd::set_text(1, "Routine: no autonomous");
        controller.set_text(0, 0, "Routine: no auton");
        routine = 0;
    });

    pros::lcd::register_btn2_cb([]()
    {
        pros::lcd::set_text(1, "Routine: right side autonomous");
        controller.set_text(0, 0, "Routine: right auton");
        routine = 2;
    });
}

void disabled() {}

void competition_initialize() {}

void autonomous()
{
    pros::lcd::set_text(0, "Starting autonomous...");

    routine = 99;

    // Left side autonomous routine (manual selection)
    if (routine == 1) { routine_auton_left(); }

    // Right side autonomous routine (manual selection)
    else if (routine == 2) { routine_auton_right(); }

    // Autonomous Skills routine
    else if (routine == 10) { routine_auton_skills(); }

    // Test autonomous routine
    else if (routine == 99) { routine_auton_test(); }

    // Automatic autonomous selection
    else if (routine == 3)
    {
        // Left side autonomous routine
        if ((gps_pos_x > 0.0 && gps_pos_y < 0.0) || (gps_pos_x < 0.0 && gps_pos_y > 0.0)) { routine_auton_left(); }

        // Right side autonomous routine
        if ((gps_pos_x > 0.0 && gps_pos_y > 0.0) || (gps_pos_x < 0.0 && gps_pos_y < 0.0)) { routine_auton_right(); }
    }
}

void opcontrol()
{
    pros::lcd::set_text(0, "Starting driver control...");
    controller.set_text(0, 0, "Front: outtake");

    // Repeat until driver control is over.
	while (true)
	{        
        routine_driver_control();
        pros::delay(100);
	}
}
