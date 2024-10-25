#include <stdarg.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "lab2_ex8.h"

typedef struct point {
    double x;
    double y;
} point;

typedef struct finaly_ans {
    int len;
    int * mass;
} finaly_ans;


int toDecimal(char * str, int len, int sys);
char * from_decimal_to_system(int decimal, int system);
int Caprecar(char * current, int base);
int Task1(int count, ...);
double Task2(double point, int n, ...);
finaly_ans Task3(int base, int count, ...);

int Task1(int count, ...) {
    if (count < 3) {
        return NO;
    }
    va_list args;
    va_start(args, count);
    point points[count];
    for (int i = 0; i < count; i++) {
        points[i] = va_arg(args, point);
    }
    va_end(args);
    double cross;
    int sign;
    int main_sign = 0;
    for (int i = 0; i < count; i++) {
        // вторая точка тройки
        int j = (i + 1) % count;
        // третья точка тройки
        int k = (i + 2) % count;
        // нахождение направления векторного произведения
        cross = (points[j].x - points[i].x) * (points[k].y - points[j].y) - 
        (points[j].y - points[i].y) * (points[k].x - points[j].x);
        if (cross > 0) {
            sign = 1;
        }
        else if (cross < 0) {
            sign = -1;
        }
        else {
            sign = 0;
        }

        if (sign == 0) {
            continue;
        }
        if (main_sign == 0) {
            main_sign = sign;
            continue;
        }
        if (sign == main_sign) {
            continue;
        }
        else {
            return NO;
        }

    }
    return OK;

}

double Task2(double point, int n, ...) {
    va_list args;
    double ans = 0;
    double current_point = pow(point, n);
    va_start(args, n);
    for (int i = 0; i <= n; i++) {
        ans += va_arg(args, double) * current_point;
        current_point /= point;
    }
    va_end(args);
    return ans;

}

finaly_ans Task3(int base, int count, ...) {
    va_list args;
    va_start(args, count);
    char * current;
    finaly_ans ans;
    ans.mass = (int *) malloc(count * sizeof(int));
    if (ans.mass == NULL) {
        ans.len = -1;
        return ans;
    }
    ans.len = count;
    int status;
    for (int i = 0; i < count; i++) {
        current = va_arg(args, char *);
        status = Caprecar(current, base);
        switch(status) {
            case OVERFLOW:
                ans.mass[i] = OVERFLOW;
                break;
            case NO:
                ans.mass[i] = NO;
                break;
            case MEM_TROUBLE:
                ans.mass[i] = MEM_TROUBLE;
                break;
            case INCORRECT_ARGUMENTS:
                ans.mass[i] = INCORRECT_ARGUMENTS;
                break;
            case OK:
                ans.mass[i] = OK;
                break;

        }
        
    }
    return ans;
}

int Caprecar(char * current, int base) {
    for (int i = 0; i < strlen(current); i++) {
        if (current[i] >= '0' && current[i] < '0' + base) {
            continue;
        }
        else if (toupper(current[i]) >= 'A' && toupper(current[i]) < 'A' + base) {
            continue;
        }
        else {
            return INCORRECT_ARGUMENTS;
        }
    }
    int len = strlen(current);
    int decimal_current = toDecimal(current, len, base);
    if (decimal_current == OVERFLOW) {
        return OVERFLOW;
    }
    if (decimal_current > INT_MAX / decimal_current) {
        return OVERFLOW;
    }
    int decimal_square = decimal_current * decimal_current;
    char * square = from_decimal_to_system(decimal_square, base);
    if (strlen(square) - len != len) {
        return NO;
    }
    char * right = (char *) malloc (len + 1);
    char left[len + 1];
    for (int i = 0; i < len; i++) {
        left[i] = square[i];
        right[i] = square[len + i];

    }
    free(square);
    left[len] = 0;
    right[len] = 0;
    int status = AdditionInSystem(base, left, &right);
    if (status == INCORRECT_ARGUMENTS) {
        free(right);
        return INCORRECT_ARGUMENTS;
    }
    else if (status == MEM_TROUBLE) {
        free(right);
        return MEM_TROUBLE;
    }
    else if (status == OK) {
        if (strcmp(right, current) == 0) {
            free(right);
            return OK;
        }
        else {
            free(right);
            return NO;
        }
    }


}

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
            return OVERFLOW;
        }
        ans += (int)pow(sys, i) * num;
    }
    return ans;

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
            ans[i] = 'A' + current - 10;
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

