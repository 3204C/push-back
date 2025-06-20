/**
 * @headerfile intake.hpp
 * 
 * This file declares all variables and functions used for the intake's
 * autonomous and driver control movement.
 */

#ifndef INTAKE_HPP
#define INTAKE_HPP

/**
 * Spins the intake motor in a specified direction indefinitely.
 * 
 * @param is_intake_pressed Returns 1 if the intake button is pressed and 0 if not.
 * @param is_outtake_pressed Returns 1 if the outtake button is pressed and 0 if not.
 */
void intake_spin(int is_intake_pressed, int is_outtake_pressed);

/**
 * Spins the intake motor in a specified direction for an amount of time.
 * 
 * @param is_intake_pressed Returns 1 if the intake button is pressed and 0 if not.
 * @param is_outtake_pressed Returns 1 if the outtake button is pressed and 0 if not.
 * @param duration The amount of time (in ms) the intake motor spins for.
 */
void intake_spin(int is_intake_pressed, int is_outtake_pressed, int duration);

#endif
