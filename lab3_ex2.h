#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

typedef struct vector {
    int size;
    double *mass;
} vector;

typedef enum statuses {
    OK,
    MEM_TROUBLE,
    INCORRECT_ARGUMETNS
} statuses;

typedef struct finaly_ans {
    int status;
    vector * ans1;
    vector * ans2;
    vector * ans3;
    int size1;
    int size2;
    int size3;
    int anses1;
    int anses2;
    int anses3;
} finaly_ans;

typedef double (*universal) (vector, void *);

int InitVector(vector * vec, int size);
int createVector(vector * vec, int size, ...);
double FirstNorm(vector vec, void * arg);
double SecondNorm(vector vec, void * arg);
double ThirdNorm(vector vec, void * arg);
finaly_ans Task(int n, int count, double eps, double p, vector * matrix, universal FirstNorm, 
universal SecondNorm, universal ThirdNorm, ...);
