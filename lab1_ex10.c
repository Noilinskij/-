#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


int toDecimal(char * str, int len, int sys);
char * from_decimal_to_system(int decimal, int system);
int system_check(char * str, int len, int system);
int strcmp2(char * str, char * max);

int toDecimal(char * str, int len, int sys) {
    int ans = 0;
    int num = 0;
    for (int i = len - 1; i >= 0; i--) {
        if (str[len - i - 1] >= 'a') {
                num = str[len - i - 1] - 'a' + 10;
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

int toDecimal2(char * str, int len, int sys) {
    int ans = 0;
    int num = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] >= 'a') {
                num = str[i] - 'a' + 10;
        }
        else {
            num = str[i] - '0';
        }
        if (ans > INT_MAX - ans * (sys - 1) - num) {
            return -1;
        }
        ans = ans * sys + num;

    }
    return ans;
}

char * from_decimal_to_system(int decimal, int system) {
    char * ans = (char *) malloc(33);
     if (ans == NULL) {
        printf("Memory trouble");
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
        while(decimal >= currentOsn) {
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
    if (ans[0] != 0) { 
        return ans;
    }
    return "0";

}

int system_check(char * str, int len, int system) {
    if (system > 10) {
        for (int i = 0; i < len; i++) {
            if (str[i] >= 'a' && str[i] <= 'z' && str[i] >= system - 10 + 'a') {
                return 1;
            }
        }
    }
    else {
        for (int i = 0; i < len; i++) {
            if ((str[i] >= 'a' && str[i] <= 'z') || str[i] >= system + '0') {
                return 1;
            }
        }
    }
    return 0;

}

int strcmp2(char * str, char * max) {
    int len_str = 0;
    int len_max = 0;
    int i = 0;
    while (str[i] != 0) {
        i++;
    }
    i++;
    len_str = i;
    i = 0;
    while (max[i] != 0) {
        i++;
    }
    i++;
    len_max = i;
    if (len_str > len_max) { 
        return 1;
    }
    else if (len_str < len_max) { 
        return -1;
    }
    else {
        return strcmp(str, max);
    }
}


int main() {
    char current = 0;
    int system = 0;
    // max для int и 1 терминальный
    int len = 33;
    int max_len = 0;
    char * str = (char *) malloc(len);
    if (str == NULL) {
        printf("Memory trouble\n");
        return 1;
    }
    char * max = (char *) malloc(len);
    if (max == NULL) {
        printf("Memory trouble\n");
        free(str);
        return 1;
    }
    memset(str, 0, len);
    memset(max, 0, len);
    int i = 0;
    int flag = 0;
    int zeroflag = 0;
    while((scanf("%c", &current)) != EOF) {
        if (((current >= '0' && current <= '9') || (current >= 'a' && current <= 'z') 
        || (current == 'S' && i == 0)) && flag != 1) {
            if (current == '0' && i == 0) {
                zeroflag = 1;
                continue;
            }
            if (i != len) {
                zeroflag = 0;
                str[i] = current;
                i++;
            }
            else {
                flag = 1;
            }
        }
        else if (flag == 1 && current == '\n') {
            printf("incorrect number\n");
            memset(str, 0, 33);
            flag = 0;
            i = 0;
        }
        else if (flag == 0 && current == '\n') {
            if (zeroflag) {
                str[0] = '0';
                i++; 
            }
            if (str[0] == 'S' && str[1] == 't' && str[2] == 'o' 
            && str[3] == 'p' && str[4] == 0) {
                break;
            }
            if (system == 0) {
                system = atoi(str);
                memset(str, 0, i);
                i = 0;
                if (system < 2 || system > 36) {
                    printf("incorrect system");
                    return 1;
                }
                continue;

            }
            if (!system_check(str, i, system)) {
                if(strcmp2(str, max) > 0) {
                    strcpy(max, str);
                    max_len = i;
                }
            }
            else {
                printf("incorrect number\n");
            }
            memset(str, 0, i);
            i = 0;
        }
        else {
            flag = 1;
            i = 0;
        }
    }
    int max_decimal = toDecimal2(max, max_len, system);
    if (max_decimal == -1) {
        printf("overflow");
        return 1;
    }
    if (max[0] != 0) {
        printf("%s\n", max);
        char * ans = from_decimal_to_system(max_decimal, 9);
        printf("%s\n", ans);
        free(ans);
        ans = from_decimal_to_system(max_decimal, 18);
        printf("%s\n", ans);
        free(ans);
        ans = from_decimal_to_system(max_decimal, 27);
        printf("%s\n", ans);
        free(ans);
        ans = from_decimal_to_system(max_decimal, 36);
        printf("%s\n", ans);
        free(ans);
    }
    else {
        printf("No answer\n");
    }

    free(str);
    free(max);
    return 0;


}