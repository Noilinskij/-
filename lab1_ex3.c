#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>


typedef enum kOpts {
    Opt_Q,
    Opt_M,
    Opt_T
} kOpts;

int float_checker(char * s);
int int_checker(char * s);
int getOpts(int argc, char ** argv, kOpts *opt);
void HandlerOptQ(char ** argv);
void HandlerOptM(char ** argv);
void HandlerOptT(char ** argv);

int getOpts(int argc, char ** argv, kOpts *opt){
    if (argc < 4) return 1;
    if (argc == 6 && (strcmp(argv[1], "-q") == 0 || strcmp(argv[1], "/q") == 0)){
        *opt = Opt_Q;
        if (!float_checker(argv[2]) && !float_checker(argv[3]) 
        && !float_checker(argv[4]) && !float_checker(argv[5])) {
            return 0;
        }
        return 1;

    }
    else if (argc == 4 && (strcmp(argv[1], "-m") == 0 || strcmp(argv[1], "/m") == 0)){
        *opt = Opt_M;
        if (!int_checker(argv[2]) && !int_checker(argv[3]) && strcmp(argv[2], "0") && strcmp(argv[3], "0")) return 0;
        *opt = Opt_M;
        return 1;

    }
    else if (argc == 6 && (strcmp(argv[1], "-t") == 0 || strcmp(argv[1], "/t") == 0)){
        *opt = Opt_T;
        if (!float_checker(argv[2]) && !float_checker(argv[3]) 
        && !float_checker(argv[4]) && !float_checker(argv[5])) {
            return 0;
        }
        return 1;

    }
    return 1;
}

int float_checker(char * s){
    int fl = 0;
    for (int i = 0; i < strlen(s); i++){
        if (isdigit(s[i])) continue;
        else if (s[i] == '.' && i != 0 && i != strlen(s) - 1) fl++;
        else if (s[i] == '-' && i == 0) continue;
        else return 1;
    }
    if (fl <= 1){
        return 0;
    }
    return 1;
}

int int_checker(char * s){
    for (int i = 0; i < strlen(s); i++){
        if (isdigit(s[i])) continue;
        else if (s[i] == '-' && i == 0) continue;
        return 1;
    }
    return 0;
}

void HandlerOptQ(char ** argv){
    float eps = atof(argv[2]);
    float first = atof(argv[3]);
    float second = atof(argv[4]);
    float third = atof(argv[5]); // сделать проверку на 0
    float ans1 = 0;
    float ans2 = 0;
    int fl = 0;
    if ((second * second - 4 * first * third >= eps) && first > eps){
        ans1 = (-second - sqrtf(second * second - 4 * first * third)) / (2 * first);
        ans2 = (-second + sqrtf(second * second - 4 * first * third)) / (2 * first);
        printf("%fx^2 + %fx + %f = 0    Answer: x = %f and x = %f\n", first, second, third, ans1, ans2);
        fl++;
    }
    if ((third * third - 4 * first * second >= eps) && first > eps){
        ans1 = (-third - sqrtf(third * third - 4 * first * second)) / (2 * first);
        ans2 = (-third + sqrtf(third * third - 4 * first * second)) / (2 * first);
        printf("%fx^2 + %fx + %f = 0    Answer: x = %f and x = %f\n", first, third, second, ans1, ans2);
        fl++;
    }
    if ((first * first - 4 * third * second >= eps) && second > eps){
        ans1 = (-first - sqrtf(first * first - 4 * third * second)) / (2 * second);
        ans2 = (-first + sqrtf(first * first - 4 * third * second)) / (2 * second);
        printf("%fx^2 + %fx + %f = 0    Answer: x = %f and x = %f\n", second, first, third, ans1, ans2);
        fl++;
    }
    if ((third * third - 4 * first * second >= eps) && second > eps){
        ans1 = (-third - sqrtf(third * third - 4 * first * second)) / (2 * second);
        ans2 = (-third + sqrtf(third * third - 4 * first * second)) / (2 * second);
        printf("%fx^2 + %fx + %f = 0    Answer: x = %f and x = %f\n", second, third, first, ans1, ans2);
        fl++;
    }
    if ((first * first - 4 * third * second >= eps) && third > eps){
        ans1 = (-first - sqrtf(first * first - 4 * third * second)) / (2 * third);
        ans2 = (-first + sqrtf(first * first - 4 * third * second)) / (2 * third);
        printf("%fx^2 + %fx + %f = 0    Answer: x = %f and x = %f\n", third, first, second, ans1, ans2);
        fl++;
    }
    if ((second * second - 4 * third * first >= eps) && third > eps){
        ans1 = (-second - sqrtf(second * second - 4 * third * first)) / (2 * third);
        ans2 = (-second + sqrtf(second * second - 4 * third * first)) / (2 * third);
        printf("%fx^2 + %fx + %f = 0    Answer: x = %f and x = %f\n", third, second, first, ans1, ans2);
        fl++;
    }
    if (!fl) printf("No answers");

}

void HandlerOptM(char ** argv){;
    int first = atoi(argv[2]); 
    int second = atoi(argv[3]);
    if (first % second == 0) printf("Yes");
    else printf("No");
}

void HandlerOptT(char ** argv){
    float eps = atof(argv[2]);
    float first = atof(argv[3]);
    float second = atof(argv[4]);
    float third = atof(argv[5]);
    if (first + second - third >= eps && 
    first + third - second >= eps && 
    third + second - first >= eps) printf("Yes");
    else printf("No");

}


int main(int argc, char ** argv) {
    kOpts opt = 0;
    void (*handlers[6])(char **) = {
        HandlerOptQ,
        HandlerOptM,
        HandlerOptT

    };
    if (getOpts(argc, argv, &opt)){
        printf("incorrect arguments");
        return 1;
    }
    handlers[opt](argv);


}