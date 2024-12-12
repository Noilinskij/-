#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef enum kOpts {
    OPT_H,
    OPT_P,
    OPT_S,
    OPT_E,
    OPT_A,
    OPT_F
} kOpts;

int GetOpts(int argc, char** argv, kOpts *option, int *number); 
void HandlerOptH(int number); 
void HandlerOptP(int number);
void HandlerOptS(int number);
void HandlerOptE(int number);
void HandlerOptA(int number);
void HandlerOptF(int number);

int GetOpts(int argc, char** argv, kOpts *option, int *number){
    if (argc != 3) return 1;
    for (int i = 0; i < strlen(argv[1]); i++){
        if (!isdigit(argv[1][i]) && !(i == 0 && argv[1][i] == '-')){
            return 1;
        }
    }
    *number = atoi(argv[1]);
    if (strcmp(argv[2], "-h") == 0 || strcmp(argv[2], "/h") == 0){
        *option = OPT_H;
        return 0;
    }
    if (strcmp(argv[2], "-p") == 0 || strcmp(argv[2], "/p") == 0){
        *option = OPT_P;
        return 0;
    }
    if ((strcmp(argv[2], "-s") == 0 || strcmp(argv[2], "/s") == 0) && *number > 0){
        *option = OPT_S;
        return 0;
    }
    if ((strcmp(argv[2], "-e") == 0 || strcmp(argv[2], "/e") == 0) && *number <= 10){
        *option = OPT_E;
        return 0;
    }
    if (strcmp(argv[2], "-a") == 0 || strcmp(argv[2], "/a") == 0){
        *option = OPT_A;
        return 0;
    }
    if (strcmp(argv[2], "-f") == 0 || strcmp(argv[2], "/f") == 0){
        *option = OPT_F;
        return 0;
    }
    return 1;

}

void HandlerOptH(int number){
    int fl = 1;
    for (int i = 1; i <= 100; i++){
        if (i % number == 0){ 
            printf("%d\n", i);
            fl = 0;
        }

    }
    if (fl){
        printf("No answer");
    }

}

void HandlerOptP(int number){
    int fl = 1; // 1 не простое
    if (number < 0){
        printf("x not is prime");
    }
    else{
        for (int i = 2; i < sqrt(number); i++){
            if (number % i == 0){
                printf("x not is prime");
                fl = 0;
                break;
            }
        }
        if (fl){
            printf("x is prime");
        }
    }

}

void HandlerOptS(int number){
    int count = 1;
    int currentOsn = 1;
    int currentAns = 0;
    while(currentOsn <= number){
        currentOsn *= 16;
        count++;
    }
    count--;
    currentOsn /= 16;
    while (number > 0){
        while(number >= currentOsn){
            number -= currentOsn;
            currentAns += 1;
        }
        if (currentAns < 10) printf("%d ", currentAns);
        else{
            switch(currentAns){
                case 10:
                    printf("A ");
                    break;
                case 11:
                    printf("B ");
                    break;
                case 12:
                    printf("C ");
                    break;
                case 13:
                    printf("D ");
                    break;
                case 14:
                    printf("E ");
                    break;
                case 15:
                    printf("F ");
                    break;

            }
        }
        count--;
        currentAns = 0;
        currentOsn /= 16;
    }
    while(count > 0){
        printf("0 ");
        count--;
    }
}

void HandlerOptE(int number){
    int fl = 0;
    if (number < 0){
        fl = 1;
        number = -number;
    }
    for (int i = 1; i <= 10; i++){
        for (int j = 1; j <= number; j++){
            if (!fl) printf("%.f ", pow(i, j)); // тк pow возвращает double
            else printf("1/%.f ", pow(i, j));
        }
        printf("\n");
    }
    
}

void HandlerOptA(int number){
    int sum = 0; // сделать проверку на переполнение
    if (number < 0) printf("1");
    else{
        for (int i = 1; i <= number; i++){
            sum += i;
        }
        printf("%d", sum);
    }
    
}

void HandlerOptF(int number){
    if (number < 0){
        printf("No answer");
    }
    else{
        int fac = 1;
        for (int i = 1; i <= number; i++){
            fac *= i;
        }
        printf("%d", fac);
    }

}



int main (int argc, char** argv) {
    kOpts opt = 0;
    int procceed_number = 0;
    void (*handlers[6])(int) = {
        HandlerOptH,
        HandlerOptP,
        HandlerOptS,
        HandlerOptE,
        HandlerOptA,
        HandlerOptF

    };


    if (GetOpts(argc, argv, &opt, &procceed_number)) {
        printf("%s", "Incorrect arguments");
        return 1;
    }
    handlers[opt](procceed_number);
    return 0;
}