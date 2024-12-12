#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef enum statuses {
    OK,
    INCORRECT_ARGUMENTS,
    INCORRECT_FILENAMES,
    OPEN_PROBLEM_FIRST,
    OPEN_PROBLEM_SECOND,
    OPEN_PROBLEM_OUT,
    MEM_PROBLEM
} statuses;

typedef enum kOpts {
    OPT_R,
    OPT_A
} kOpts;


int getOpts(int argc, char ** argv, kOpts * option, char ** first_in, 
char ** second_in, char ** out);
char * from_decimal_to_system(int decimal, int system);
int HandlerOptA(char * first_in, char * second_in, char * out);
int HandlerOptR (char * first_in, char * second_in, char * out);

int getOpts(int argc, char ** argv, kOpts * option, 
char ** first_in, char ** second_in, char ** out) {
    if ( argc < 2) {
        return INCORRECT_ARGUMENTS;
    }
    if ( argc == 5 && (strcmp(argv[1], "-r") == 0 || strcmp(argv[1], "/r"))) {
        if (strcmp(argv[2], argv[4]) == 0 || strcmp(argv[3], argv[4]) == 0) {
            return INCORRECT_FILENAMES;
        }
        *first_in = argv[2];
        *second_in = argv[3];
        *out = argv[4];
        *option = OPT_R;
        return OK;

    }
    else if ( argc == 4 && (strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "/a"))) {
        if (strcmp(argv[2], argv[3]) == 0) {
            return INCORRECT_FILENAMES;
        }
        *first_in = argv[2];
        *out = argv[3];
        *option = OPT_A;
    }
    else {
        return INCORRECT_ARGUMENTS;
    }
    return OK;

}

int HandlerOptR (char * first_in, char * second_in, char * out) {
    FILE * first_input;
    FILE * second_input;
    FILE * output;
    char symbol_first;
    char symbol_second;
    if ((first_input = fopen(first_in, "r")) == NULL) {
        return OPEN_PROBLEM_FIRST;
    }
    if ((second_input = fopen(second_in, "r")) == NULL) {
        fclose(first_input);
        return OPEN_PROBLEM_SECOND;
    }
    if ((output = fopen(out, "w")) == NULL) {
        fclose(first_input);
        fclose(second_input);
        return OPEN_PROBLEM_OUT;
    }
    // флаг для переключения считывания
    int flag = 0;
    while ((symbol_first = fgetc(first_input)) != EOF && (symbol_first == '\n' || 
    symbol_first == '\t' || symbol_first == ' ')) {
            continue;
    }
    while ((symbol_second = fgetc(second_input)) != EOF && (symbol_second == '\n' || 
    symbol_second == '\t' || symbol_second == ' ')) {
            continue;
    }
    // флаг для пропуска пробельных символов
    int skip_flag = 0;
    // выходы через break
    while (1) {
        if (flag == 0) {
            fprintf(output, "%c", symbol_first);
            // считываем и выводим лексему
            while ((symbol_first = fgetc(first_input)) != EOF && symbol_first != '\n' && 
            symbol_first != '\t' && symbol_first != ' ') {
                fprintf(output, "%c", symbol_first);
            }
            // пропускаем пробельные символы
            while ((symbol_first = fgetc(first_input)) != EOF && (symbol_first == '\n' || 
            symbol_first == '\t' || symbol_first == ' ')) {
                continue;
            }
            if (symbol_first == EOF) {
                // вывод оставшегося файла
                skip_flag = 0;
                fprintf(output, " %c", symbol_second);
                while ((symbol_second = fgetc(second_input)) != EOF) {
                    if (symbol_second != '\t' && symbol_second != ' ' && symbol_second != '\n') {
                        skip_flag = 0;
                        fprintf(output, "%c", symbol_second);
                    }
                    else {
                        if (skip_flag == 0) {
                            fprintf(output, " ");
                        }
                        skip_flag = 1;
                    }
                }
                break;
            }
            fprintf(output, " ");
            flag = 1;
        }

        else {
            fprintf(output, " %c", symbol_second);
            // считываем и выводим лексему
            while ((symbol_second = fgetc(second_input)) != EOF && 
            symbol_second != '\n' && symbol_second != '\t' && symbol_second != ' ') {
                fprintf(output, "%c", symbol_second);
            }
            // пропускаем пробельные символы
            while ((symbol_second = fgetc(second_input)) != EOF && (symbol_second == '\n' || 
            symbol_second == '\t' || symbol_second == ' ')) {
                continue;
            }
            if (symbol_second == EOF) {
                skip_flag = 0;
                fprintf(output, " %c", symbol_first);
                // вывод оставшегося файла
                while ((symbol_first = fgetc(first_input)) != EOF) {
                    if (symbol_first != '\t' && symbol_first != ' ' && symbol_first != '\n') {
                        skip_flag = 0;
                        fprintf(output, "%c", symbol_first);
                    }
                    else {
                        if (skip_flag == 0) {
                            fprintf(output, " ");
                        }
                        skip_flag = 1;
                    }
                }
                break;
            }
            fprintf(output, " ");
            flag = 0;
        }

    }
    fclose(first_input);
    fclose(second_input);
    fclose(output);
    return OK;
    
}

int HandlerOptA(char * first_in, char * second_in, char * out) {
    int count = 0;
    FILE * input;
    FILE * output;
    char symbol;
    int size = 0;
    char * current = (char *) malloc(1);
    if (current == NULL) {
        return MEM_PROBLEM;
    }
    if ((input = fopen(first_in, "r")) == NULL) {
        return OPEN_PROBLEM_FIRST;
    }
    if ((output = fopen(out, "w")) == NULL) {
        fclose(input);
        return OPEN_PROBLEM_OUT;
    }
    int skip_flag = 0;
    while ((symbol = fgetc(input)) != EOF) {
        if (symbol != ' ' && symbol != '\t' && symbol != '\n') {
            skip_flag = 0;
            size++;
            char * tmp = (char *) realloc(current, size + 1);
            if (tmp == NULL) {
                return MEM_PROBLEM;
            }
            current = tmp;
            current[size - 1] = symbol;
            current[size] = 0;
        }
        else {
            if (skip_flag == 0) {
                skip_flag = 1;
                count++;
                if (count % 10 == 0) {
                    for (int i = 0; i < strlen(current); i++) {
                        char * ans = from_decimal_to_system(tolower(current[i]), 4);
                        fprintf(output, "%s ", ans);
                        free(ans);
                    }
                    memset(current, 0, strlen(current));
                }
                else if (count % 2 == 0) {
                     for (int i = 0; i < strlen(current); i++) {
                        current[i] = tolower(current[i]);
                    }
                    fprintf(output, "%s ", current);
                    memset(current, 0, strlen(current));
                }
                else if (count % 5 == 0) {
                    for (int i = 0; i < strlen(current); i++) {
                        char * ans = from_decimal_to_system(current[i], 8);
                        fprintf(output, "%s ", ans);
                        free(ans);
                    }
                    memset(current, 0, strlen(current));
                }
                else {
                    fprintf(output, "%s ", current);
                    memset(current, 0, strlen(current));
                }
            }
            size = 0;

        }
    }
    count++;
    if (count % 10 == 0) {
        for (int i = 0; i < strlen(current); i++) {
            char * ans = from_decimal_to_system(tolower(current[i]), 4);
            fprintf(output, "%s ", ans);
            free(ans);
        }
        memset(current, 0, strlen(current));
        }
        else if (count % 2 == 0) {
            for (int i = 0; i < strlen(current); i++) {
                current[i] = tolower(current[i]);
            }
            fprintf(output, "%s ", current);
            memset(current, 0, strlen(current));
        }
        else if (count % 5 == 0) {
            for (int i = 0; i < strlen(current); i++) {
                char * ans = from_decimal_to_system(current[i], 8);
                fprintf(output, "%s ", ans);
                free(ans);
            }
            memset(current, 0, strlen(current));
        }
        else {
            fprintf(output, "%s ", current);
            memset(current, 0, strlen(current));
        }
    free(current);
    fclose(input);
    fclose(output);
    


}

char * from_decimal_to_system(int decimal, int system) {
    char * ans = (char *) malloc(33);
     if (ans == NULL) {
        return NULL;
    }
    int len = 33;
    int currentOsn = 1;
    int i = 0;
    int current = 0;
    memset(ans, 0, len);
    while (decimal >= currentOsn) {
        currentOsn *= system;
    }
    currentOsn /= system;
    while(decimal > 0) {
        while(decimal >= currentOsn
        ) {
            current++;
            decimal -= currentOsn;
        }
        if (current < 10) {
            ans[i] = '0' + current;
        }
        else {
            ans[i] = 'a' + current - 10;
        }
        current = 0;
        currentOsn /= system;
        i++;
    }
    while (currentOsn > 0) {
        ans[i] = '0';
        currentOsn /= system;
        i++;
    }
    if (ans[0] != 0) { 
        return ans;
    }
    return "0";

}


int main(int argc, char ** argv) {
    char * first_in;
    char * second_in;
    char * out;
    kOpts option;
    int ans = getOpts(argc, argv, &option, &first_in, &second_in, &out);
    switch(ans) {
        case OK:
            break;
        case INCORRECT_ARGUMENTS:
            printf("incorrect argumetns");
            return INCORRECT_ARGUMENTS;
        case INCORRECT_FILENAMES:
            printf("incorrect filenames");
            return INCORRECT_ARGUMENTS;
    }
    int (*handlers[2])(char *, char *, char *) = {
        HandlerOptR,
        HandlerOptA

    };
    ans = handlers[option](first_in, second_in, out);
    switch(ans) {
        case OK:
            return OK;
        case OPEN_PROBLEM_FIRST:
            printf("first file could not be opened");
            return OPEN_PROBLEM_FIRST;
        case OPEN_PROBLEM_SECOND:
            printf("second file could not be opened");
            return OPEN_PROBLEM_SECOND;
        case OPEN_PROBLEM_OUT:
            printf("out file could not be opened");
            return OPEN_PROBLEM_OUT;
        case MEM_PROBLEM:
            printf("memory trouble");
            return MEM_PROBLEM;

    }

}