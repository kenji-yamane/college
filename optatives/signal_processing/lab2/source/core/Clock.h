//
// Created by mmaximo on 25/04/16.
//

#ifndef KALMAN_FILTERING_CLOCK_H
#define KALMAN_FILTERING_CLOCK_H

/**
 * Class to measure execution time.
 */
class Clock {
private:
    double timeLastTic;

public:
    /**
     * Default constructor.
     */
    Clock();
    /**
     * Returns current time in seconds.
     *
     * @return current time in seconds.
     */
    static double getCurrentTime();
    /**
     * Starts an chronometer. Works similarly to the function tic() of MATLAB.
     * To measure computation time, use the followling template:
     *
     * Clock c;
     * c.tic();
     * // Computation whose time we want to measure
     * double t = c.toc();
     */
    void tic();
    /**
     * Returns elapsed time since last tic() call.
     *
     * @return elapsed time since last tic() call.
     */
    double toc();
};

#endif //KALMAN_FILTERING_CLOCK_H
