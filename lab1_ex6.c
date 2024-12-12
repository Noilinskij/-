#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

typedef enum errors {
    OK,
    INCORRECT_ARGUMENTS
} errors;


int getArg(int argc, char ** argv, float * eps);
float task_a(float eps);
float task_b(float eps);
float task_c(float eps);
float task_d(float eps);


int getArg(int argc, char ** argv, float * eps) {
    if (argc != 2) {
        return 1;
    }
    char * s = argv[1];
    int fl = 0;
    for (int i = 0; i < strlen(s); i++) {
        if (isdigit(s[i])) continue;
        else if (s[i] == '.' && i != 0 && i != strlen(s)) fl++;
        else if (s[i] == '-' && i == 0) continue;
        else return 1;
    }
    if (fl <= 1) {
        *eps = atof(s);
        return 0;
    }
    return 1;
}

float task_a(float eps) {
    float n = 1;
    float step = 1;
    float current_accuracy = 10;
    float ans_prev = 0;
    float ans_current = 0;
    float current_x = 0;
    while (current_accuracy > eps) {
        ans_prev = ans_current;
        ans_current = 0;
        current_x = 0;
        step = 1 / n;
        for (int i = 0; i < n; i++) {
            ans_current += (log(1 + current_x + step / 2) / (current_x + step / 2)) * step;
            current_x += step;
        }
        n = 2 * n;
        current_accuracy = fabs(ans_current - ans_prev) / 3;

    }
    return ans_current;

}

float task_b(float eps) {
    float n = 1;
    float step = 1;
    float current_accuracy = 10;
    float ans_prev = 0;
    float ans_current = 0;
    float current_x = 0;
    while (current_accuracy > eps) {
        ans_prev = ans_current;
        ans_current = 0;
        current_x = 0;
        step = 1 / n;
        for (int i = 0; i < n; i++) {
            ans_current += expf(-(((current_x + step / 2) * (current_x + step / 2)) / 2)) * step;
            current_x += step;
        }
        n = 2 * n;
        current_accuracy = fabs(ans_current - ans_prev) / 3;

    }
    return ans_current;

}

float task_c(float eps) {
    float n = 1;
    float step = 1;
    float current_accuracy = 10;
    float ans_prev = 0;
    float ans_current = 0;
    float current_x = 0;
    while (current_accuracy > eps) {
        ans_prev = ans_current;
        ans_current = 0;
        current_x = 0;
        step = 1 / n;
        for (int i = 0; i < n; i++) {
            ans_current += log(1 / (1 - (current_x + step / 2))) * step;
            current_x += step;
        }
        n = 2 * n;
        current_accuracy = fabs(ans_current - ans_prev) / 3;

    }
    return ans_current;

}

float task_d(float eps) {
    float n = 1;
    float step = 1;
    float current_accuracy = 10;
    float ans_prev = 0;
    float ans_current = 0;
    float current_x = 0;
    while (current_accuracy > eps) {
        ans_prev = ans_current;
        ans_current = 0;
        current_x = 0;
        step = 1 / n;
        for (int i = 0; i < n; i++) {
            ans_current += powf(current_x + step / 2, current_x + step / 2) * step;
            current_x += step;
        }
        n = 2 * n;
        current_accuracy = fabs(ans_current - ans_prev) / 3;

    }
    return ans_current;

}

int main(int argc, char ** argv) {
    float eps;
    if (getArg(argc, argv, &eps)) {
        printf("incorrect arguments");
        return INCORRECT_ARGUMENTS;
    }
    printf("Answer for a: %f\n", task_a(eps));
    printf("Answer for b: %f\n", task_b(eps));
    printf("Answer for c: %f\n", task_c(eps));
    printf("Answer for d: %f\n", task_d(eps));
    return OK;

}