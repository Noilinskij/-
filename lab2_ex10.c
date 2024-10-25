#include "lab2_ex10.h"

int main() {
    double * ans;
    int degree = 2;
    int status = Task(0.0001, 2, &ans, degree, 1.0, -2.0, 1.0);
    if (status == OK) { 
        for (int i = 0; i <= degree; i++) {
            printf("%f\n", ans[i]);
        }
        free(ans);
    }
    else if (status == MEM_TROUBLE) {
        printf("memory trouble");
        return MEM_TROUBLE;
    }
    printf("\n");
    degree = 2;
    status = Task(0.0001, 1, &ans, degree, 0.0, 0.0, 1.0);
    if (status == OK) { 
        for (int i = 0; i <= degree; i++) {
            printf("%f\n", ans[i]);
        }
        free(ans);
    }
    else if (status == MEM_TROUBLE) {
        printf("memory trouble");
        return MEM_TROUBLE;
    }

}