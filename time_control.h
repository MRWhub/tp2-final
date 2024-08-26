#ifndef MY_SLEEP_H_INCLUDED
#define MY_SLEEP_H_INCLUDED

/**
 * @brief Suspends the execution of the program for a specified number of seconds.
 * @details This function pauses the execution of the program for the given number of seconds.
 *          The time can be a fractional value (e.g., 2.5 seconds).
 * @param seconds - The number of seconds to suspend the execution.
 */
void my_sleep(double seconds);

/**
 * @brief Suspends the execution of the program for a specified number of seconds.
 * @details This function pauses the execution of the program for the given number of seconds,
 *          using the unsigned integer type for the delay duration.
 * @param seconds - The number of seconds to suspend the execution (in whole seconds).
 */
void stopping(unsigned int seconds);

/**
 * @brief Generates a random time value between 2 and 3 seconds.
 * @details This function generates a random floating-point time value for use in simulations or timing-related scenarios.
 * @return A random double value representing time.
 */
double pre_random_time();

#endif // MY_SLEEP_H_INCLUDED
