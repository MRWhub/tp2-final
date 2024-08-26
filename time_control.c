#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "time_control.h"
#include <errno.h>
#define TIME_UNITY 1

#include <time.h>

void my_sleep(double seconds) {
    /**
     * @brief Suspends execution for a specified number of seconds using nanosleep.
     *
     * @param seconds Number of seconds to suspend execution.
     */
    struct timespec req, rem;
    req.tv_sec = (time_t)seconds;
    req.tv_nsec = (seconds - req.tv_sec) * 1e9;

    while (nanosleep(&req, &rem) == -1 && errno == EINTR) {
        req = rem;
    }
}



void stopping(unsigned int sec) {
/**
 * @brief Displays a countdown and then stops the program.
 *
 * @param sec Number of seconds for the countdown.
 */
    for (int i = sec; i > 0; i--) {
        printf("\n\nClosing Program in %d second(s)....", i);
        my_sleep(1);
    }
    printf("\nProgram closed.\n");

}



double pre_random_time() {
    /**
     * @brief Generates a random time duration between 2 and 3 second.

     * @param None.
     *
     * @return A random time duration as a double, within the range [2, 3).
     */
    srand(time(NULL));


    double fracTempo = (double)rand() / RAND_MAX;


    return (2.0+ fracTempo); // returns double rando time

    }
