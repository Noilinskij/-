#include <stdarg.h>
#include <stdlib.h>

typedef enum statuses{
    OK,
    INCORRECT_ARGUMENTS,
    NO,
    MEM_TROUBLE
} statuses;

typedef struct finaly_ans{
    statuses status;
    statuses * answer;
    int count;
} finaly_ans;



int gcd(int first, int second);
statuses Checker(int system, int precision, double number);
finaly_ans Task(int system, int precision, int count, ...);


finaly_ans Task(int system, int precision, int count, ...)  {
    finaly_ans result;
    result.answer = (statuses *) malloc(sizeof(statuses) * count);
    if (result.answer == NULL) {
        result.status = MEM_TROUBLE;
    }
    result.count = count;
    if (system < 2 || system > 36 || count <= 0) {
        result.status = INCORRECT_ARGUMENTS;
        return result;
    }
    int checker = precision;
    while (checker > 1) {
        if (checker % 10 != 0) {
            result.status = INCORRECT_ARGUMENTS;
            return result;
        }
        checker /= 10;
    }
    va_list args;
    va_start(args, count);
    double current;
    statuses ans;
    for (int i = 0; i < count; i++) {
        current = va_arg(args, double);
        if (current > 1.0 || current < 0) {
            result.status = INCORRECT_ARGUMENTS;
            return result;
        }
        ans = Checker(system, precision, current);
        result.answer[i] = ans;


    }
    result.status = OK;
    va_end(args);
    return result;
}


statuses Checker(int system, int precision, double number) {
    // представляем в виде обыкновенной десятичной дроби
    int chisl = (int) (number * precision);
    int znam = precision;
    // сократили дробь
    int div = gcd(chisl, znam);
    chisl /= div;
    znam /= div;
    int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    int len = 11;
    // разбиваем на простые делители, кратные основанию системы
    for (int i = 0; i < len && primes[i] <= system; i++) {
        while (znam % primes[i] == 0 && system % primes[i] == 0) {
            znam /= primes[i];
        }
    }
    if (znam == 1) {
        return OK;
    }
    return NO;



}

int gcd(int first, int second) {
    int tmp = first;
    while (first != 0) {
        tmp = first;
        first = second % first;
        second = tmp; 
    }
    return second;
}