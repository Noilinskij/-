#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

typedef enum statuses {
    OK,
    MEM_TROUBLE
} statuses;

// вычисление результата функции
double func_res(double a, double * coefficents, int degree) {
    double ans = 0;
    double current_a = 1.0;
    for (int i = 0;i <= degree; i++) {
        ans += coefficents[i] * current_a;
        current_a *= a;
    }
    return ans;

}


// полином Тейлора
int Task(double eps, double a, double ** ans, int degree, ...) {
    va_list args;
    va_start(args, degree);
    if (ans == NULL) {
        return MEM_TROUBLE;
    }
    *ans = (double *) malloc((degree + 1) * sizeof(double));
    if (*ans == NULL) {
        return MEM_TROUBLE;
    }
    double * current = (double *) malloc((degree + 1) * sizeof(double));
    if (current == NULL) {
        free(*ans);
        return MEM_TROUBLE;
    }
    for (int i = 0; i <= degree; i++) {
        current[i] = va_arg(args, double);
    }
    va_end(args);
    double fact = 1.0;
    **ans = func_res(a, current, degree);
    double current_degree = degree - 1;
    for (int i = 1; i <= degree; i++) {
        // вычисление производной
        for (int j = 0; j <= current_degree; j++) {
            current[j] = current[j + 1] * (j + 1);
        }
        fact *= i;
        (*ans)[i] = func_res(a, current, current_degree) / fact;
        current_degree--;

    }
    free(current);
    return OK;
}
