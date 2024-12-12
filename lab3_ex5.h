#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct Student {
    unsigned int id;
    char * name;
    char * surname;
    char * group;
    unsigned char * rating;
    float medium;

} Student;

typedef enum statuses {
    OK,
    INCORRECT_ARGUMENTS,
    OPEN_PROBLEM,
    MEM_PROBLEM
} statuses;

typedef enum situations {
    ID,
    NAME,
    SURNAME,
    GROUP,
    RATING
} situations;

int GetArgs(int argc, char ** argv, char ** in, char ** out);
int MassFulling(Student ** mass, char * in, int * mass_count, float * medium_rate, int * max_current_count);
int FinderID(Student * mass, int mass_count, unsigned int id, char * out);
int Finder(Student * mass, int mass_count, char * find_what, char * out, int flag);
int Best(Student * mass, int mass_count, float medium_rate, float eps, char * out);
int CmpId(const void * a, const void * b);
int CmpName(const void * a, const void * b);
int CmpSurname(const void * a, const void * b);
int CmpGroup(const void * a, const void * b);
int SortToFile(Student * mass, int mass_count, situations situation, char * out);
int FinderID(Student * mass, int mass_count, unsigned int id, char * out);
int max(int a, int b);