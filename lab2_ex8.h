#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum statuses {
    OK,
    INCORRECT_ARGUMENTS,
    MEM_TROUBLE,
    OVERFLOW,
    NO
} statuses;

typedef struct  answer {
    statuses status;
    char * ans;


} answer;

int min(int a, int b);
int max(int a, int b);
int AdditionInSystem(int system, char * current, char ** ans);
char * ReverseStr (char * s);
answer Task(int system, int count, ...);

answer Task(int system, int count, ...) {
    answer finaly_ans;
    if (system < 2 || system > 36 || count <= 0) {
        finaly_ans.status = INCORRECT_ARGUMENTS;
        return finaly_ans;
    }
    va_list args;
    va_start(args, count);
    char * current;
    int size = 0;
    char * ans = (char *) malloc(1);
    // определяем единственный байт как 0, чтобы strlen был корректен
    memset(ans, 0, 1);
    if (ans == NULL) {
        finaly_ans.status = MEM_TROUBLE;
        return finaly_ans;
    }
    statuses status;
    for (int i = 0; i < count; i++) {
        current = va_arg(args, char *);
        status = AdditionInSystem(system, current, &ans);
        if (status == MEM_TROUBLE) {
            finaly_ans.status = status;
            return finaly_ans;
        }
        else if (status == INCORRECT_ARGUMENTS) {
            finaly_ans.status = status;
            return finaly_ans;
        }

    }
    finaly_ans.status = OK;
    finaly_ans.ans = ans;
    return finaly_ans;
}

int AdditionInSystem(int system, char * current_s, char ** ans_s) {
    char * ans = ReverseStr(*ans_s);
    if (ans == NULL) {
        return MEM_TROUBLE;
    }
    char * current = ReverseStr(current_s);
    if (current == NULL) {
        return MEM_TROUBLE;
    }
    int len_ans = strlen(ans);
    int len_current = strlen(current);
    int decimal_current;
    int decimal_ans;
    int current_sum_result;
    int remainder = 0;
    // 1 под возможный новый разряд и один под \0
    char * tmp = (char *) realloc(ans, max(len_ans, len_current) + 1 + 1);
    if (tmp == NULL) {
        free(current);
        free(ans);
        return MEM_TROUBLE;
    }
    // добавленную память зануляем
    memset(tmp + len_ans, 0, max(len_ans, len_current) - len_ans + 1 + 1);
    ans = tmp;
    for (int i = 0; i < len_current; i++) {
        current[i] = toupper(current[i]);

        // валидируем цифры
        if ((system <= 10 && (current[i] < '0' + system && current[i] >= '0')) || 
        (system > 10 && ((current[i] <= '9' && current[i] >= '0') || (current[i] < 'A' + system - 10 && current[i] >= 'A')))) {
            // переводим цифры в десятичную
            if (current[i] == 0) {
                decimal_current = 0;
            }
            else if (current[i] - 'A' < 0) {
                decimal_current = current[i] - '0';
            }
            else {
                decimal_current = current[i] - 'A' + 10;
            }
            if (ans[i] == 0) {
                decimal_ans = 0;
            }
            else if (ans[i] - 'A' < 0) {
                decimal_ans = ans[i] - '0';
            }
            else {
                decimal_ans = ans[i] - 'A' + 10;
            }
            current_sum_result = (decimal_ans + decimal_current + remainder) % system;
            remainder = (decimal_ans + decimal_current + remainder) / system;
            if (current_sum_result >= 10) {
                ans[i] = current_sum_result + 'A' - 10;
            }
            else {
                ans[i] = current_sum_result + '0';
            }
            
            

        }
        else {
            free(ans);
            free(current);
            return INCORRECT_ARGUMENTS;
        }
    }
    int i = len_current;
    // продолжаем заполнять ans, если остался остаток
    while(remainder != 0) {
        if (ans[i] == 0) {
            decimal_ans = 0;
        }
        else if (ans[i] - 'A' < 0) {
            decimal_ans = ans[i] - '0';
        }
        else {
            decimal_ans = ans[i] - 'A' + 10;
        }
        current_sum_result = (decimal_ans + remainder) % system;
        remainder = (decimal_ans + remainder) / system;
         if (current_sum_result >= 10) {
            ans[i] = current_sum_result + 'A' - 10;
        }
        else {
            ans[i] = current_sum_result + '0';
        }
        i++;
    };
    free(*ans_s);
    *ans_s = ReverseStr(ans);
    free(ans);
    free(current);
    return OK;

}

int min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

char * ReverseStr (char * s) {
    if (s == NULL) {
        return NULL;
    }
    int len = strlen(s);
    char * ans = (char *) malloc(len + 1);
    if (ans == NULL) {
        return NULL;
    }
    for (int i = len - 1; i >= 0; i--) {
        ans[len - 1 - i] = s[i];
    }
    ans[len] = 0;
    return ans;
}
