#include <stdio.h>
#include "lab2_ex9.h"


int main () {
    finaly_ans result;
    result = Task(20, 1000000, 3, 0.2, 0.3, 0.6);
    switch(result.status) {
        case INCORRECT_ARGUMENTS:
            printf("incorrect arguments");
            free(result.answer);
            return INCORRECT_ARGUMENTS;
        case OK:
            for (int i = 0; i < result.count; i++) {
                if (result.answer[i] == OK) {
                    printf("%d is OK\n", i + 1);
                }
                else {
                    printf("%d not is OK\n", i + 1);
                }
            }
            free(result.answer);
            return OK;
    }

}