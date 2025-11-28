/**
 * @headerfile outtake.hpp
 * 
 * This file declares all variables and functions used for the outtake's
 * autonomous and driver control movement.
 */

#ifndef OUTTAKE_HPP
#define OUTTAKE_HPP

/**
 * Spins the outtake motor in a specified direction indefinitely.
 * 
 * @param is_outward Returns 1 if the outward button is pressed and 0 if not.
 * @param is_inward Returns 1 if the inward button is pressed and 0 if not.
 * @param voltage The voltage of the outtake motor when spinning.
 */
void outtake_spin(int is_outward, int is_inward, int voltage);

/**
 * Spins the outtake motor in a specified direction for an amount of time.
 * 
 * @param is_outward Returns 1 if the outward button is pressed and 0 if not.
 * @param is_inward Returns 1 if the inward button is pressed and 0 if not.
 * @param voltage The voltage of the outtake motor when spinning.
 * @param duration The amount of time (in ms) the outtake motor spins for.
 */
void outtake_spin(int is_outward, int is_inward, int voltage, int duration);

/**
 * Lifts the outtake using pneumatics in a specified direction.
 * 
 * @param is_upward Returns 1 if the upward button is pressed and 0 if not.
 * @param is_downward Returns 1 if the downward button is pressed and 0 if not.
 */
void outtake_lift(int is_upward, int is_downward);

#endif
