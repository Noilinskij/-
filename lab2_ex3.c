#include "lab2_ex3.h"

int main() {
    finalyAns * answer = Task("a  \nd", "file1.txt", "file3.txt", NULL);
    if (answer == NULL) {
        printf("Memory trouble or zero input files");
        return MEMORY_TROUBLE;
    }
    for (int i = 0; i < answer[0].count_files; i++) {
        if (answer[i].status == OK) {
            printf("%s %d\n", answer[i].filename, answer[i].ans_for_file_len);
            for (int j = 0; j < answer[i].ans_for_file_len; j++) {
                printf("%d %d\n", answer[i].ans_for_file[j].str_number, answer[i].ans_for_file[j].symbol_number);
            }
            free(answer[i].ans_for_file);
        }
        else {
            if (answer[i].status == OPEN_PROBLEM) {
                printf("%s open problem\n", answer[i].filename);
                free(answer);
                return OPEN_PROBLEM;
            }
            else if (answer[i].status == MEMORY_TROUBLE) {
                printf("%s memory trouble\n", answer[i].filename);
                free(answer);
                return MEMORY_TROUBLE;
            }
        }
    }
    free(answer);
    return OK;
}