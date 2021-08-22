#ifndef SOLVE
#define SOLVE

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void mhd_map(double phases[3], bool noise);
void rk_fourth_order(double phases[3], double step, bool noise);

#endif
