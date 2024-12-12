#include <stdio.h>
#include "lab2_ex7.h"


int main() {
    double ans;
    int status;
    status = Task(-5, 10, 0.000001, Func1, &ans);
    switch(status) {
        case OK:
            printf("%.15f\n", ans);
            break;
        case NO_ANSWER:
            printf("no answer\n");
            break;
        case INCORRECT_EPSILON:
            printf("epsilon must be positive\n");
    }
    status = Task(1.8, 2.2, 0.000001, Func2, &ans);
    switch(status) {
        case OK:
            printf("%.15f\n", ans);
            break;
        case NO_ANSWER:
            printf("no answer\n");
            break;
        case INCORRECT_EPSILON:
            printf("epsilon must be positive\n");
    }
    status = Task(-3, 4, 0.000001, Func3, &ans);
    switch(status) {
        case OK:
            printf("%.15f\n", ans);
            break;
        case NO_ANSWER:
            printf("no answer\n");
            break;
        case INCORRECT_EPSILON:
            printf("epsilon must be positive\n");
    }
    
}