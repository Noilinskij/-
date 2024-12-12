#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


float * task(int len, float * A, float * B) {
    float difference = 2000;
    float * C = (float *)malloc(sizeof(float) * len + 1);
    if (C == NULL) {
        printf("Memory trouble");
        return (float *) 1;
    }
    for (int i = 0; i < len; i++) {
        C[i] = A[i] + B[i];
        difference = fabs(A[i] - B[i]);
        for (int j = 0; j < len; j++) {
            if (fabs(A[i] - B[j]) < difference) {
                difference = fabs(A[i] - B[j]);
                C[i] = A[i] + B[j];
            }
        }
    }
    return C;
}


int main() {
    srand(time(NULL));
    int len = rand() % (10000 - 10 + 1) + 10;
    printf("%d", len);
    float * A = (float *)malloc(sizeof(float) * len + 1);
    float * B = (float *)malloc(sizeof(float) * len + 1);
    if (A == NULL || B == NULL) {
        printf("Memory trouble");
        free(A);
        free(B);
        return 1;
    }
    for (int i = 0; i < len; i++) {
        A[i] = (float) (rand() + 1) / (float)(RAND_MAX) * (1000 + 1000) - 1000;
        B[i] = (float) (rand() + 1) / (float)(RAND_MAX) * (1000 + 1000) - 1000;
    }
    float * C = task(len, A, B);
    for (int i = 0; i < len; i++) {
        printf("%f %f\n", A[i], C[i]);
    }
    free(A);
    free(B);
    free(C);
    return 0;
    

}