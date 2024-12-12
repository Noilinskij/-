#include <stdio.h>
#include "lab2_ex1.h"

int main( int argc, char ** argv) {
    kOpts option;
    if (getArgs(argc, &option, argv)) {
        printf("incorrect argumetns");
        return INCORRECT_ARGUMENTS;
    }
    switch (option) {
        case OPT_L:
            int ans_l = SizeOfStr(argv[2]);
            printf("%d\n", ans_l);
            return OK;
        case OPT_R:
            char * ans_r = ReverseStr(argv[2]);
            if (ans_r == NULL) {
                printf("memory trouble");
                return MEM_TROUBLE;
            }
            printf("%s\n", ans_r);
            free(ans_r);
            return OK;
        case OPT_U:
            char * ans_u = TaskU(argv[2]);
            if (ans_u == NULL) {
                printf("memory trouble");
                return MEM_TROUBLE;
            }
            printf("%s\n", ans_u);
            free(ans_u);
            return OK;
        case OPT_N:
            char * ans_n = TaskN(argv[2]);
            if (ans_n == NULL) {
                printf("memory trouble");
                return MEM_TROUBLE;
            }
            printf("%s\n", ans_n);
            free(ans_n);
            return OK;
        case OPT_C:
            char * ans_c = TaskC(argc, argv);
            if (ans_c == NULL) {
                printf("memory trouble");
                return MEM_TROUBLE;
            }
            printf("%s\n", ans_c);
            free(ans_c);
            return OK;
    }
}