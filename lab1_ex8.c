#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>


int task(int argc, char ** argv, FILE * input, FILE * output);
int toDecimal(char * str, int len, int sys);
void clearStr(char * str, int len);


// перевод в 10 сс
int toDecimal(char * str, int len, int sys) {
    int ans = 0;
    int num = 0;
    for (int i = len - 1; i >= 0; i--) {
        if (str[len - i - 1] >= 'A') {
                num = str[len - i - 1] - 'A' + 10;
        }
        else num = str[len - i - 1] - '0';
        // проверка на переполнение
        if (ans > INT_MAX - (int)pow(sys, i) * num) {
            return -1;
        }
        ans += (int)pow(sys, i) * num;
    }
    return ans;

}

void clearStr(char * str, int len) {
    for (int i = 0; i < len; i++){
        str[i] = '\0';
    }
}


int task(int argc, char ** argv, FILE * input, FILE * output) {
    // проверили входящие аргументы и открыли файл
    if (argc != 3) {
        printf("incorrect arguments");
        return 1;
    }
    if ((input = fopen(argv[1], "r")) == NULL) {
        printf("The input file could not be opened");
        return 1;
    }
    if ((output = fopen(argv[2], "w")) == NULL) {
        printf("The output file could not be opened");
        fclose(input);
        return 1;
    }

    char current;
    int flag = 0;
    char sys = '1';
    int current_decimal = 0;
    int k = 0;
    int nulls = 0;

    // выделяем память под максимально возможное число в мин сс до переполнения 
    // int (4 байта, в 2 сс - 32 байта и 1 '\0')
    char * current_str = malloc(sizeof(char) * 32 + 1);
    if (current_str == NULL) {
        printf("Memory trouble");
        fclose(input);
        fclose(output);
        return 1;
    }
    int len = 33;
    clearStr(&*current_str, len);
    while((current = toupper(fgetc(input))) != EOF) {
        if ((current >= 'A' && current <= 'Z') || isdigit(current)) {
            // встретили число
            if (flag == 0 && current != '0') {
                k = 0;
                current_str[k] = current;
                flag = 1;
                if (current > sys) {
                    sys = current;
                }
            }
            // идем по числу
            else if (flag == 0 && current == '0') {
                nulls++;
            }
            else if (flag == 1 && (k + 1 < len)) {
                k++;
                current_str[k] = current;
                if (current > sys) {
                    sys = current;
                }
            }
            // переполнение массива ( = переполнение int) (продолжаем идти до КОНЦА большого числа)
            else if (current != '0') flag = 2;

        }
        // закончили с числом
        else if (current == ' ' || current == '\t' || current == '\n') {
            if (flag == 1) {
                if (sys >= 'A') {
                    sys = sys - 'A' + 10 + 1;
                }
                else sys = sys - '0' + 1;
                current_decimal = toDecimal(current_str, k + 1, sys);
                if (current_decimal != -1) fprintf(output, "%s %d %d\n", 
                current_str, sys, current_decimal);
                else fprintf(output, "%s %d int overflow\n", current_str, sys);
                clearStr(&*current_str, len);
                flag = 0;
                nulls = 0;
                k = 0;
                sys = '1';
                current_decimal = 0;
            }
            else if (flag == 2) {
                fprintf(output, "overflow\n");
                clearStr(&*current_str, len);
                flag = 0;
                nulls = 0;
                k = 0;
                sys = '1';
                current_decimal = 0;
            }
            else if (flag == 0 && nulls != 0) {
                nulls = 0;
                current_decimal = toDecimal("0", 1, 1);
                if (current_decimal != -1) fprintf(output, "0 %d %d\n", 1, current_decimal);
                else fprintf(output, "%s %d int overflow\n", current_str, sys);
                clearStr(&*current_str, len);
                flag = 0;
                nulls = 0;
                k = 0;
                sys = '1';
                current_decimal = 0;
            }
        }
        // встретили мусор
        else {
            if (flag == 1 && nulls > 0) {
                fprintf(output, "incorrect argumetns\n");
                flag = 0;
                clearStr(&*current_str, len);
                k = 0;
                nulls = 0;
                sys = '1';
                current_decimal = 0;
            }
        }

    }
    if (flag == 1) {
        if (sys >= 'A') {
                    sys = sys - 'A' + 10 + 1;
                }
        else sys = sys - '0' + 1;
        current_decimal = toDecimal(current_str, k + 1, sys);
        if (current_decimal != -1) fprintf(output, "%s %d %d\n", 
        current_str, sys, current_decimal);
        else fprintf(output, "%s %d int overflow\n", current_str, sys);
        clearStr(&*current_str, len);
        flag = 0;
        k = 0;
        nulls = 0;
        sys = '1';
        current_decimal = 0;
    }
    fclose(input);
    fclose(output);
    free(current_str);
    return 0;

}



int main(int argc, char ** argv) {
    FILE * input;
    FILE * output;
    if (task(argc, argv, input, output)) return 1;

}