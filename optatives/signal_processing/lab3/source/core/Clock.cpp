//
// Created by mmaximo on 25/04/16.
//

#include "Clock.h"

#include <sys/time.h>

Clock::Clock() : timeLastTic(-1.0) {
}

double Clock::getCurrentTime() {
    struct timeval tv;
    struct timezone tz;

    gettimeofday(&tv, &tz);
    return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

void Clock::tic() {
    timeLastTic = getCurrentTime();
}

double Clock::toc() {
    return (getCurrentTime() - timeLastTic);
}