/**
 * @headerfile intake.hpp
 * 
 * This file declares all variables and functions used for the intake's
 * autonomous and driver control movement.
 */

#ifndef INTAKE_HPP
#define INTAKE_HPP

/**
 * Spins the intake motors in a specified direction indefinitely.
 * 
 * @param is_inward Returns 1 if the inward button is pressed and 0 if not.
 * @param is_outward Returns 1 if the outwards button is pressed and 0 if not.
 * @param voltage The voltage of the intake motors when spinning.
 */
void intake_spin(int is_inward, int is_outward, int voltage);

/**
 * Spins the intake motors in a specified direction for an amount of time.
 * 
 * @param is_inward Returns 1 if the inward button is pressed and 0 if not.
 * @param is_outward Returns 1 if the outward button is pressed and 0 if not.
 * @param voltage The voltage of the intake motors when spinning.
 * @param duration The amount of time (in ms) the intake motor spins for.
 */
void intake_spin(int is_inward, int is_outward, int voltage, int duration);

#endif
