/**
 * @headerfile conveyor.hpp
 * 
 * This file declares all variables and functions used for the conveyor belt's
 * autonomous and driver control movement.
 */

#ifndef CONVEYOR_HPP
#define CONVEYOR_HPP

/**
 * Spins the conveyor belt motor in a specified direction indefinitely.
 * 
 * @param is_upward Returns 1 if the upward button is pressed and 0 if not.
 * @param is_downwards Returns 1 if the downward button is pressed and 0 if not.
 */
void conveyor_spin(int is_upward, int is_downward);

/**
 * Spins the conveyor belt motor in a specified direction for an amount of time.
 * 
 * @param is_upward Returns 1 if the upward button is pressed and 0 if not.
 * @param is_downward Returns 1 if the outward button is pressed and 0 if not.
 * @param duration The amount of time (in ms) the intake motor spins for.
 */
void conveyor_spin(int is_upward, int is_downward, int duration);

#endif
