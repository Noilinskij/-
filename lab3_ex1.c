#include "lab3_ex1.h"

int Func(int number, int r, int ans[]) {
    int base = 1;
    // умножаем на 2 r раз
    for (int i = 0; i < r; i = PlusOne(i)) {
        base = base << 1;
    }
    // максимальная длина int в двоичном представлении
    int len = 32;
    int count = MinusOne(len);
    int remainder;
    while (number >= base) {
        remainder = ((number >> r) << r) ^ number;
        number = number >> r;
        ans[count] = remainder;
        count = MinusOne(count);
    }
    ans[count] = number;
    return count;

}

int PlusOne(int number) {
    int bit = 1;
    // идем по битам 1, пока не встретим 0 и нулим их, чтобы потом вместо 0 поставить 1
    // и таким образом прибавим единицу
    while ((bit & number) > 0) {
        number = ~bit & number;
        bit = bit << 1;
    }
    number = number | bit;
    return number;

}

int MinusOne(int number) {
    int bit = 1;
    while ((bit & number) == 0) {
        number = bit | number;
        bit = bit << 1;
    }
    number = ~bit & number;
    return number;
}


int main() {
    int len = 32;
    int ans[len];
    int count = Func(64, 4, ans);
    for (int i = count; i < len; i = PlusOne(i)) {
        if (ans[i] > 9) {
            for (int j = 0; j < 'A'; j = PlusOne(j)) {
                ans[i] = PlusOne(ans[i]);
            }
            for (int j = 10; j > 0; j = MinusOne(j)) {
                ans[i] = MinusOne(ans[i]);
            }
            printf("%c", ans[i]);
        }
        else {
            printf("%d", ans[i]);
        }
    }
}


int strlen(const char* str) {
    int size = 0;
    for (int i = 0; str[i]; i++) {
        size++;
    }
    return size;
}