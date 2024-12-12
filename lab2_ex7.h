#include <math.h>


typedef enum statuses {
    OK,
    NO_ANSWER,
    INCORRECT_EPSILON
} statuses;

double Func1(double x) {
    return 1.0 - 2.0 * x;
}

double Func2(double x) {
    return (1.0 - x) * (1.0 - x) - 1;
}

double Func3(double x) {
    return (x - 1) * (x - 1);
}


int Task(double left, double right, double eps, double (*func) (double), double * ans) {
    if (func(left) * func(right) > 0) {
        return NO_ANSWER;
    }
    if (eps <= 0) {
        return INCORRECT_EPSILON;
    }
    while ((right - left) > eps) {
        *ans = (left + right) / 2.0;
        if (func(*ans) * func(left) <= 0) {
            right = *ans;
        }
        else {
            left = *ans;
        }
    }
    *ans = (left + right) / 2.0;
    return OK;

}