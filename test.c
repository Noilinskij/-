#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    char* name;
    int age;
} Person;

typedef struct Node {
    int value;
    struct Node* next;
} Node;



// Сравнение по возрасту
int comparePersonAge(const void* a, const void* b) {
    Person* p1 = (Person*)a;
    Person* p2 = (Person*)b;
    return (p1->age - p2->age);
}


int gorner(const char* str, int base) {
    if (str == NULL || (base > 36 || base < 2)) {
        return -1;
    }
    int result = 0;
    while(*str) {
        if ('0' <= *str && *str <= '9') {
            result = result * base + *str - '0';
        }
        else if ('A' <= toupper(*str) && toupper(*str) < 'A' + base) {
            result = result * base + toupper(*str) - 'A' + 10;
        }
        else {
            return -1;
        }
        str++;
    }
    return result;
}

char* ungorner(unsigned int num, int base) {
    int current;
    char * ans = (char*) calloc(sizeof(char), 2);
    int size = 2;
    int count = 0;
    if (num == 0) {
        ans[0] = '0';
        return ans;
    }
    while(num > 0) {
        current = num % base;
        if (size == count + 1) {
            size = 2 * (count + 1) + 1;
            char* tmp = (char*) realloc(ans, size);
            if (tmp == NULL) {
                free(ans);
                return NULL;
            }
            ans = tmp;
        }
        num /= base;
        if (0 <= current && current <= 9) {
            ans[count] = current + '0';
        }
        else if (10 <= current && current < base) {
            ans[count] = 'A' + current - 10;
        }
        count++;

    }
    ans[count] = '\0';
    char tmp;
    int zeroflag = 0;
    for (int i = 0; i < count / 2; i++) {
        tmp = ans[i];
        ans[i] = ans[count - i - 1];
        ans[count - i - 1] = tmp;
    }
    return ans;
}

void freeint(int* x) {
    free(x);
}

int main() {
    int* x = (int*) malloc(sizeof(int));
    freeint(x);

}