#include <stdio.h>
#include <stdarg.h>
#include <math.h>

typedef enum statuses {
    OK,
    INCORRECT_ARGUMENTS
} statuses;

double GeometricMean(int count, ...);
double MyPow(double number, int degree);

double GeometricMean(int count, ...) {
    // список аргументов
    va_list args;
    double composition = 1.0;
    // указатель на последний обязательный аргумент
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        composition *= va_arg(args, double);
    }
    va_end(args);
    return pow(composition, 1.0 / (double) count);
    
}

double MyPow(double number, int degree) {
    if (degree >=  0) {
        if (degree == 0) {
            return 1;
        }
        else if (degree % 2 == 0) {
            double x = MyPow(number, degree / 2);
            return x * x;
        }
        else {
            double x = MyPow(number, (degree - 1) / 2);
            return number * x * x;
        }
    }
    else {
        return 1.0 / MyPow(number, -degree);
    }

}

