#include "lab3_ex3.h"

int GetArgs(int argc, char ** argv, char ** in, char ** out, kOpts * opt) {
    if (argc != 4) {
        return INCORRECT_ARGUMENTS;
    }
    if (strcmp(argv[1], argv[2]) == 0) {
        return INCORRECT_FILENAMES;
    }
    if (strlen(argv[2]) == 2 && (argv[2][0] == '/' || argv[2][0] == '-')) {
        if (argv[2][1] == 'a') {
            *opt = OPT_A;
        }
        else if (argv[2][1] == 'd') {
            *opt = OPT_D;
        }
        else {
            return INCORRECT_ARGUMENTS;
        }

    }
    *in = argv[1];
    *out = argv[3];
    return OK;


}

int StrChecker(char * s) {
    if (strlen(s) == 0) {
        return INCORRECT_ARGUMENTS;
    }
     for (int i = 0; i < (int) strlen(s); i++) {
        if (isalpha(s[i])) {
            continue;
        }
        else {
            return INCORRECT_ARGUMENTS;
        }
    }
    return OK;
}

int EmployeeCmpOptA(const void * a, const void * b) {
    const Employee *first = (const Employee *) a;
    const Employee *second = (const Employee *) b;
    int eps = 0.0001;
    if (fabs(first->salary - second->salary) < eps) {
        if (strcmp(first->surname, second->surname) == 0) {
            if (strcmp(first->name, second->name) == 0) {
                if (first->id == second->id) {
                    return 0;
                }
                else if (first->id > second->id) {
                    return 1;
                }
                else {
                    return -1;
                }
            }
            else {
                return strcmp(first->name, second->name);
            }
        }
        else {
            return strcmp(first->surname, second->surname);
        }

    }
    else if (first->salary - second->salary > eps) {
        return 1;
    }
    else {
        return -1;
    }
}

int EmployeeCmpOptD(const void * a, const void * b) {
    const Employee *first = (const Employee *) a;
    const Employee *second = (const Employee *) b;
    int result = EmployeeCmpOptA(first, second);
    if (result == 0) {
        return 0;
    }
    else if (result > 0) {
        return -1;
    }
    return 1;

}

int Task (char * in, char * out, kOpts opt) {
    FILE * input;
    FILE * output;
    if ((input = fopen(in, "r")) == NULL) {
        return OPEN_PROBLEM;
    }
    if ((output = fopen(out, "w")) == NULL) {
        fclose(input);
        return OPEN_PROBLEM;
    }
    Employee * mass = NULL;
    Employee * tmp = NULL;
    int count;
    int number = 0;
    int current_id;
    char name[50];
    char surname[50];
    float salary;
    int size_mass = 0;
    while((count = fscanf(input, "%d %s %s %f", &current_id, name, surname, &salary)) == 4) {
        if (number >= size_mass) {
            size_mass = (number + 1) * 2;
            tmp = (Employee *) realloc(mass, size_mass * sizeof(Employee));
            if (tmp == NULL) {
                fclose(input);
                fclose(output);
                return MEM_TROUBLE;
            }
            mass = tmp;
        }
        if (StrChecker(name) == OK && StrChecker(surname) == OK) {
            mass[number].id = current_id;
            strcpy(mass[number].name, name);
            strcpy(mass[number].surname, surname);
            mass[number].salary = salary;
        }
        else {
            free(mass);
            fclose(input);
            fclose(output);
            return INCORRECT_ARGUMENTS;
        }
        number++;

    }
    if (count != -1) {
        free(mass);
        fclose(input);
        fclose(output);
        return INCORRECT_ARGUMENTS;
    }
    if (opt == OPT_A) {
        qsort(mass, number, sizeof(Employee), EmployeeCmpOptA);
    }
    else if (opt == OPT_D) {
        qsort(mass, number, sizeof(Employee), EmployeeCmpOptD);
    }
    for (int i = 0; i < number; i++) {
        fprintf(output, "%d %s %s %f\n", mass[i].id, mass[i].name, mass[i].surname, mass[i].salary);
    }
    fclose(input);
    fclose(output);
    free(mass);
    return OK;


}

int main(int argc, char ** argv) {
    char * in;
    char * out;
    kOpts opt;
    statuses status;
    if ((status = GetArgs(argc, argv, &in, &out, &opt))) {
        switch(status) {
            case INCORRECT_ARGUMENTS:
                printf("incorrect arguments");
                return INCORRECT_ARGUMENTS;
            case MEM_TROUBLE:
                printf("memory trouble");
                return MEM_TROUBLE;
            case OPEN_PROBLEM:
                printf("open problem");
                return OPEN_PROBLEM;
            case INCORRECT_FILENAMES:
                printf("incorrect filenames");
                return INCORRECT_FILENAMES;
            case OK:
                printf("ok");
                return OK;
        }
        
    }
    if ((status = Task(in, out, opt))) {
        switch(status) {
            case INCORRECT_ARGUMENTS:
                printf("incorrect arguments");
                return INCORRECT_ARGUMENTS;
            case MEM_TROUBLE:
                printf("memory trouble");
                return MEM_TROUBLE;
            case OPEN_PROBLEM:
                printf("open problem");
                return OPEN_PROBLEM;
            case INCORRECT_FILENAMES:
                printf("incorrect filenames");
                return INCORRECT_FILENAMES;
            case OK:
                printf("ok");
                return OK;
        }
    }
    return OK;


}