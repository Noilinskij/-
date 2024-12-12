#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

typedef enum statuses {
    OK,
    INCORRECT_ARGUMENTS,
    INCORRECT_FILENAMES,
    OPEN_PROBLEM,
    MEM_TROUBLE
} statuses;

typedef enum kOpts {
    OPT_D,
    OPT_A
} kOpts;

typedef struct Employee {
    unsigned int id;
    char name[50];
    char surname[50];
    float salary;
} Employee;

int GetArgs(int argc, char ** argv, char ** in, char ** out, kOpts * opt);
int StrChecker(char * s);
int EmployeeCmpOptA(const void * a, const void * b);
int EmployeeCmpOptD(const void * a, const void * b);
int Task (char * in, char * out, kOpts opt);
