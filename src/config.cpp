#include "main.h"

// The main controller used for the robot.
pros::Controller controller(CONTROLLER_MASTER);

// The motors on the left side of the drivetrain.
// TODO: Change port number placeholders
pros::MotorGroup drivetrain_left({1, 2});

// The motors on the right side of the drivetrain.
// TODO: Change port number placeholders
pros::MotorGroup drivetrain_right({3, 4});

// The intake motor.
// TODO: Change port number placeholder
pros::Motor intake(5);

// The GPS Sensor.
// TODO: Change port number and offset placeholders
pros::Gps gps(6, 0.0, 0.0);

// The AI Vision Sensor.
// TODO: Change port number placeholder
pros::Vision vision(7);
