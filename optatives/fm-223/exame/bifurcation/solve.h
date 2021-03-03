#ifndef SOLVE
#define SOLVE

#include <math.h>

#define FRAMES_PER_PERIOD 30
#define STEP 2*M_PI/FRAMES_PER_PERIOD

void mhd_map(double phases[3], double v);
void rk_second_order(double phases[3], double v);
void rk_fourth_order(double phases[3], double v);

#endif
