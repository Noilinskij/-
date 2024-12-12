#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


int getOpts(int argc, char ** argv, float * a, float * b);
int int_or_float_checker(char * s);
void change_max_and_min(float * mass, int len);

int getOpts(int argc, char ** argv, float * a, float * b) {
    if (argc == 3 && !int_or_float_checker(argv[1]) && !int_or_float_checker(argv[2])) {
        if (atof(argv[2]) - atof(argv[1]) > 0.000001) {
            *a = atof(argv[1]);
            *b = atof(argv[2]);
        }
        else {
            *b = atof(argv[1]);
            *a = atof(argv[2]);
        }
        return 0;
    }
    return 1;
}

int int_or_float_checker(char * s) {
    int fl = 0;
    for (int i = 0; i < strlen(s); i++) {
        if (isdigit(s[i])) continue;
        else if (s[i] == '.' && i != 0 && i != strlen(s) - 1) fl++;
        else if (s[i] == '-' && i == 0) continue;
        else return 1;
    }
    if (fl <= 1) {
        return 0;
    }
    return 1;
}

void change_max_and_min(float * mass, int len) {
    int max_pos = 0;
    int min_pos = 0;
    for (int i = 1; i < len; i++) {
        if (mass[i] > mass[max_pos]) {
            max_pos = i;
        }
        if (mass[i] < mass[min_pos]) {
            min_pos = i;

        }

    }
    float changer = mass[min_pos];
    mass[min_pos] = mass[max_pos];
    mass[max_pos] = changer;

}



int main(int argc, char ** argv) {
    srand(time(NULL));
    float a = 0;
    float b = 0;
    float mass[10];
    int len = sizeof(mass) / sizeof(mass[0]);
    if (getOpts(argc, argv, &a, &b)) {
        printf("incorrect arguments");
        return 1;
    }
    for (int i = 0; i < 10; i++) {
        // явное приведение типов и задание диапозона, 1 добавляем, чтобы было от 0 до 1 => вкл правой границы
        mass[i] = (float) (rand() + 1) / (float)(RAND_MAX) * (b - a) + a;
        printf("%f\n", mass[i]);
    }
    change_max_and_min(mass, len);
    printf("\n");
    for (int i = 0; i < 10; i++) {
        printf("%f\n", mass[i]);
    }
    return 0;

}