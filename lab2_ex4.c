#include <stdio.h>
#include "lab2_ex4.h"

int main() {
    printf("%f\n", Task2(3, 2, 1.0, 1.0, 1.0));
    printf("\n");
    int status = Task1(4, (point){0.0, 0.0}, (point){0.0, 0.0}, (point){0.0, 0.0}, (point){0.0, 0.0});
    if (status == OK) {
        printf("YES\n");
    }
    else {
        printf("NO\n");
    }
    status = Task1(5, (point){0.0, 0.0}, (point){2.0, 0.0}, (point){1.0, 1.0}, (point){2.0, 2.0}, (point){0.0, 2.0});
    if (status == OK) {
        printf("YES\n");
    }
    else {
        printf("NO\n");
    }
    printf("\n");
    finaly_ans ans = Task3(10, 3, "36", "10", "6");
    for (int i = 0; i < ans.len; i++) {
        switch(ans.mass[i]) {
            case OVERFLOW:
                printf("overflow\n");
                break;
            case NO:
                printf("NO\n");
                break;
            case MEM_TROUBLE:
                printf("memory trouble\n");
                break;
            case INCORRECT_ARGUMENTS:
                printf("incorrect arguments\n");
                break;
            case OK:
                printf("YES\n");
                break;

        }
    }
    free(ans.mass);
}