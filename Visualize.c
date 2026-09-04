#include "Visualize.h"
#include <stdio.h>
#include <stdlib.h>

void ampArrToPercent(float* ampArr, int N_adj){
    float* tempArr = malloc(N_adj * sizeof(float));
    for (int i = 0; i < N_adj; i++) {
        if (ampArr[i] + abs(MIN_DB) < 0) {
            tempArr[i] = 0.0;
        } else if ((ampArr[i] + abs(MIN_DB)) > (abs(MIN_DB) + abs(MAX_DB))) {
            tempArr[i] = 1.0;
        } else {
            tempArr[i] = ((ampArr[i] + abs(MIN_DB)) / (abs(MIN_DB) + abs(MAX_DB)));
        }
    }

    for (int i = 200; i < 250; i++) {
        printf("Bin%d:", i);
        for (int j = 0; j < (WIDTH * tempArr[i]); j++) {
            printf("#");
        }
        printf("\n");
    }

    free(tempArr);
}