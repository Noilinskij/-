#include "lab2_ex8.h"

int main() {
    answer finaly_ans = Task(36, 2, "zzzzzzzzzz", "Z");
    switch (finaly_ans.status) {
        case INCORRECT_ARGUMENTS:
            printf("incorrect argumetns");
            return INCORRECT_ARGUMENTS;
        case MEM_TROUBLE:
            printf("mem trouble");
            return MEM_TROUBLE;
        case OK:
            printf("%s", finaly_ans.ans);
            free(finaly_ans.ans);
            return OK;
    }
}