#include <stdio.h>
#include <stdlib.h>
#include "solve.h"

#define RES 1000
#define CONV 170

int main() {
    int color[RES][RES] = {0};
    double range[RES];
    double v = 0.01746;
    for (int i = 0; i < RES; i++) {
        range[i] = -2 + 4.0*i/(RES-1);
    }

    for (int i = 0; i < RES; i++) {
        printf("%d\n",i);
        for (int j = 0; j < RES; j++) {
            double start[3] = {range[i],range[j],0};
            for (int k = 0; k < CONV; k++) {
                for (int l = 0; l < FRAMES_PER_PERIOD; l++) {
                    rk_fourth_order(start,v);
                }
            }

            double last = start[1];

            // 1
            for (int k = 0; k < FRAMES_PER_PERIOD; k++)
                rk_fourth_order(start,v);
            if (fabs(start[1] - last) < 1e-3) {
                color[RES-j-1][i] = 1;
                continue;
            }

            // 3
            for (int k = 0; k < 2; k++)
                for (int l = 0; l < FRAMES_PER_PERIOD; l++)
                    rk_fourth_order(start,v);
            if (fabs(start[1] - last) < 1e-3) {
                color[RES-j-1][i] = 2;
                continue;
            }

            // 6
            for (int k = 0; k < 3; k++)
                for (int l = 0; l < FRAMES_PER_PERIOD; l++)
                    rk_fourth_order(start,v);
            if (fabs(start[1] - last) < 1e-3) {
                color[RES-j-1][i] = 4;
                continue;
            }

			// 9
            for (int k = 0; k < 3; k++)
                for (int l = 0; l < FRAMES_PER_PERIOD; l++)
                    rk_fourth_order(start,v);
            if (fabs(start[1] - last) < 1e-3) {
                color[RES-j-1][i] = 4;
                continue;
            }

            color[RES-j-1][i] = 2;
        }
    }

    FILE *f = fopen("color.txt","w");
    for (int i = 0; i < RES; i++) {
        for (int j = 0; j < RES; j++) {
            fprintf(f,"%d",color[i][j]);
            if (j != RES-1) {
                fprintf(f,",");
            }
        }
        fprintf(f,"\n");
    }
    fclose(f);
}
