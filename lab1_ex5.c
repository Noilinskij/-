#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>


int int_or_float_checker(char * s);
int getArgs(int argc, char ** argv, float * x, float * eps);
float task_a(float x, float eps);
float task_b(float x, float eps);
float task_c(float x, float eps);
float task_d(float x, float eps);

int int_or_float_checker(char * s) {
    int fl = 0;
    for (int i = 0; i < strlen(s); i++) {
        if (isdigit(s[i])) continue;
        else if (s[i] == '.' && i != 0 && i != strlen(s)) fl++;
        else if (s[i] == '-' && i == 0) continue;
        else return 1;
    }
    if (fl <= 1) {
        return 0;
    }
    return 1;
}

int getArgs(int argc, char ** argv, float * x, float * eps) {
    if (argc != 3 || int_or_float_checker(argv[1]) 
    || int_or_float_checker(argv[2])) return 1;
    *x = atof(argv[1]);
    *eps = atof(argv[2]);
    return 0;
}

float task_a(float x, float eps) {
    float n = 0;
    float current = 1;
    float ans = current;
    while (fabs(current) >= eps) {
        n++;
        current = (current * x) / n;
        if (ans > FLT_MAX - current || isnan(ans)) {
            return FLT_MAX;
        }
        ans += current;
    }
    return ans;

}


float task_b(float x, float eps) {
    float n = 0;
    float current = 1;
    float ans = current;
    while (fabs(current) >= eps) {
        n += 2;
        current = -(current * x * x) / (n * (n - 1));
        if (fabs(ans) > fabs(FLT_MAX - current) || isnan(ans)) {
            return FLT_MAX;
        }
        ans += current;
    }
    return ans;
}

float task_c(float x, float eps) {
    float n = 0;
    float current = 1;
    float ans = current;
    while(fabs(current) >= eps) {
        n += 3;
        current = ((current * x * x) * pow(n / 3, 3) * 27) / (n * (n - 1) * (n - 2));
        ans += current;
    }
    return ans;
}

float task_d(float x, float eps) {
    float n = 1;
    float current = (-1 * x * x) / 2;
    float ans = current;
    while (fabs(current) >= eps) {
        n++;
        current = (-current * (2 * n - 1) * x * x) / (2 * n);
        ans += current;
    }
    return ans;
}


int main(int argc, char ** argv) {
    float x;
    float eps;
    if (getArgs(argc, argv, &x, &eps)) {
        printf("incorrect argumetns");
        return 1;
    }
    if (task_a(x, eps) == FLT_MAX) printf("overflow for a\n");
    else printf("ans for a: %.7f\n", task_a(x, eps));

    if (task_b(x, eps) == FLT_MAX) printf("overflow for b\n");
    else printf("ans for a: %.7f\n", task_b(x, eps));

    if (fabs(x) < 1) printf("ans for c: %.7f\n", task_c(x, eps));
    else printf("No answer for c\n");

    if (x < 1) printf("ans for d: %.7f\n", task_d(x, eps));
    else printf("No answer for d\n");

    return 0;

}