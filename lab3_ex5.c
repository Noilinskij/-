#include "lab3_ex5.h"

int GetArgs(int argc, char ** argv, char ** in, char ** out) {
    if (argc != 3) {
        return INCORRECT_ARGUMENTS;
    }
    if (argv[1] == argv[2]) {
        return INCORRECT_ARGUMENTS;
    }
    *in = argv[1];
    *out = argv[2];
    return OK;
}

int MassFulling(Student ** mass, char * in, int * mass_count, float * medium_rate, int * max_current_count) {
    if (mass == NULL) {
        return INCORRECT_ARGUMENTS;
    }
    FILE * input;
    if ((input = fopen(in, "r")) == NULL) {
        return OPEN_PROBLEM;
    }
    int mass_size = 0;
    *mass_count = 0;
    char current;
    Student * tmp;
    // 0 - id, 1 - name, 2 - surname, 3 - group, 4 - rating
    situations flag = ID;
    int space_flag = 0;
    int current_size = 0;
    int current_count = 0;
    char * current_tmp;
    char * str_id = NULL;
    *medium_rate = 0;
    *mass = (Student *) malloc(sizeof(Student));
    (*mass)[*mass_count].medium = 0;
    (*mass)[*mass_count].name = NULL;
    (*mass)[*mass_count].surname = NULL;
    (*mass)[*mass_count].group = NULL;
    (*mass)[*mass_count].rating = NULL;
    while((current = getc(input)) != EOF) {
        if ((current == ' ' || current == '\n' || current == '\t') && space_flag) {
            continue;
        }
        if ((current == ' ' || current == '\n' || current == '\t') && flag != RATING) {
            if (flag == ID) {
                str_id[current_count] = 0;
                (*mass)[*mass_count].id = atoi(str_id);
            }
            current_tmp[current_count] = 0;
            flag++;
            current_count = 0;
            current_size = 0;
            space_flag = 1;
            continue;
        }
        else if ((current == ' ' || current == '\n' || current == '\t') && flag == 4) {
            (*mass)[*mass_count].medium /= 5.0;
            *medium_rate += (*mass)[*mass_count].medium;
            (*mass_count)++;
            if (*mass_count >= mass_size) {
                mass_size = 2 * (*mass_count) + 1;
                tmp = (Student *) realloc(*mass, mass_size * sizeof(Student));
                if (tmp == NULL) {
                    free(str_id);
                    fclose(input);
                    return MEM_PROBLEM;
                }
                *mass = tmp;
            }
            free(str_id);
            str_id = NULL;
            (*mass)[*mass_count].medium = 0;
            (*mass)[*mass_count].name = NULL;
            (*mass)[*mass_count].surname = NULL;
            (*mass)[*mass_count].group = NULL;
            (*mass)[*mass_count].rating = NULL;
            current_count = 0;
            current_size = 0;
            space_flag = 1;
            flag = ID;
            continue;
        }
        space_flag = 0;
        switch (flag) {
            case ID:
                if (isdigit(current)) {
                    current_count++;
                    if (current_count >= current_size) {
                        current_size = 2 * current_count + 1;
                        current_tmp = (char *) realloc(str_id, current_size * 10000000000);
                        if (current_tmp == NULL) {
                            free(str_id);
                            fclose(input);
                            return MEM_PROBLEM;
                        }
                        str_id = current_tmp;
                    }
                    str_id[current_count - 1] = current;
                }
                else {
                    free(str_id);
                    return INCORRECT_ARGUMENTS;
                }
                break;
            case NAME:
                if (isalpha(current)) {
                    current_count++;
                    if (current_count >= current_size) {
                        current_size = 2 * current_count + 1;
                        current_tmp = (char *) realloc((*mass)[*mass_count].name, current_size);
                        if (current_tmp == NULL) {
                            free(str_id);
                            fclose(input);
                            return MEM_PROBLEM;
                        }
                        (*mass)[*mass_count].name = current_tmp;
                    }
                    (*mass)[*mass_count].name[current_count - 1] = current;
                }
                else {
                    free(str_id);
                    return INCORRECT_ARGUMENTS;
                }
                break;
            case SURNAME:
                if (isalpha(current)) {
                    current_count++;
                    if (current_count >= current_size) {
                        current_size = 2 * current_count + 1;
                        current_tmp = (char *) realloc((*mass)[*mass_count].surname, current_size);
                        if (current_tmp == NULL) {
                            free(str_id);
                            fclose(input);
                            return MEM_PROBLEM;
                        }
                        (*mass)[*mass_count].surname = current_tmp;
                    }
                    (*mass)[*mass_count].surname[current_count - 1] = current;
                }
                else {
                    return INCORRECT_ARGUMENTS;
                }
                break;
            case GROUP:
                current_count++;
                if (current_count >= current_size) {
                    current_size = 2 * current_count + 1;
                    current_tmp = (char *) realloc((*mass)[*mass_count].group, current_size);
                    if (current_tmp == NULL) {
                        free(str_id);
                        return MEM_PROBLEM;
                    }
                    (*mass)[*mass_count].group = current_tmp;
                }
                (*mass)[*mass_count].group[current_count - 1] = current;
                break;
            case RATING:
                current_count++;
                if (current_count > 5) {
                    free(str_id);
                    fclose(input);
                    return INCORRECT_ARGUMENTS;
                }
                if (isdigit(current)) {
                    if (current_count >= current_size) {
                        current_size = 2 * current_count + 1;
                        current_tmp = (char *) realloc((*mass)[*mass_count].rating, current_size);
                        if (current_tmp == NULL) {
                            free(str_id);
                            return MEM_PROBLEM;
                        }
                        (*mass)[*mass_count].rating = current_tmp;
                    }
                    (*mass)[*mass_count].medium += current - '0';
                    (*mass)[*mass_count].rating[current_count - 1] = current;
                }
                else {
                    free(str_id);
                    fclose(input);
                    return INCORRECT_ARGUMENTS;
                }
                break;
            
        }
        *max_current_count = max(current_count, *max_current_count);
    }
    *medium_rate /= *mass_count;
    if (flag == 4) {
        if (current_count > 5) {
            free(str_id);
            fclose(input);
            return INCORRECT_ARGUMENTS;
        }
        mass_count++;
        flag = 0;
    }
    if (flag != 0) {
        free(str_id);
        fclose(input);
        return INCORRECT_ARGUMENTS;
    }
    free(str_id);
    fclose(input);
    return OK;
    
    
}

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int FinderID(Student * mass, int mass_count, unsigned int id, char * out) {
    if (mass == NULL || mass_count < 0) {
        return INCORRECT_ARGUMENTS;
    }
    FILE * output = fopen(out, "w");
    if (output == NULL) {
        return OPEN_PROBLEM;
    }
    for (int i = 0; i < mass_count; i++) {
        if (mass[i].id == id) {
            fprintf(output, "%s %s %s %f\n", mass[i].name, 
            mass[i].surname, mass[i].group, mass[i].medium);
            fclose(output);
            return OK;
        }
    }
    return INCORRECT_ARGUMENTS;
}

int Finder(Student * mass, int mass_count, char * find_what, char * out, int flag) {
    if (mass == NULL || mass_count < 0) {
        return INCORRECT_ARGUMENTS;
    }
    FILE * output = fopen(out, "w");
    if (output == NULL) {
        return OPEN_PROBLEM;
    }
    for (int i = 0; i < mass_count; i++) {
        switch(flag) {
            case NAME:
                if (strcmp(mass[i].name, find_what) == 0) {
                    fprintf(output, "%s %s %s %f\n", mass[i].name, 
                    mass[i].surname, mass[i].group, mass[i].medium);
                    fclose(output);
                    return OK;
                }
            case SURNAME:
                if (strcmp(mass[i].surname, find_what) == 0) {
                    fprintf(output, "%s %s %s %f\n", mass[i].name, 
                    mass[i].surname, mass[i].group, mass[i].medium);
                    fclose(output);
                    return OK;
                }
            case GROUP:
                if (strcmp(mass[i].name, find_what) == 0) {
                    fprintf(output, "%s %s %s %f\n", mass[i].name, 
                    mass[i].surname, mass[i].group, mass[i].medium);
                    fclose(output);
                    return OK;
                }
        }
    }
    return INCORRECT_ARGUMENTS;
}

int Best(Student * mass, int mass_count, float medium_rate, float eps, char * out) {
    if (mass == NULL || mass_count < 0 || medium_rate < 0 || eps < 0) {
        return INCORRECT_ARGUMENTS;
    }
    FILE * output = fopen(out, "w");
    if (output == NULL) {
        return OPEN_PROBLEM;
    }
    for (int i = 0; i < mass_count; i++) {
        if (mass[i].medium - medium_rate > eps) {
            fprintf(output, "%s %s %f\n", mass[i].name, mass[i].surname, mass[i].medium);
        }
    }
    fclose(output);
    return OK;
}

int CmpId(const void * a, const void * b) {
    Student * first = (Student *) a;
    Student * second = (Student *) b;
    if (first->id > second->id) {
        return 1;
    }
    else if (first->id == second->id) {
        return 0;
    }
    return -1;
}

int CmpName(const void * a, const void * b) {
    Student * first = (Student *) a;
    Student * second = (Student *) b;
    return strcmp(first->name, second->name);
}
int CmpSurname(const void * a, const void * b) {
    Student * first = (Student *) a;
    Student * second = (Student *) b;
    return strcmp(first->surname, second->surname);
}
int CmpGroup(const void * a, const void * b) {
    Student * first = (Student *) a;
    Student * second = (Student *) b;
    return strcmp(first->group, second->group);
}

int SortToFile(Student * mass, int mass_count, situations situation, char * out) {
    switch (situation) {
        case ID:
            qsort(mass, mass_count, sizeof(Student), CmpId);
            break;
        case NAME:
            qsort(mass, mass_count, sizeof(Student), CmpName);
            break;
        case SURNAME:
            qsort(mass, mass_count, sizeof(Student), CmpSurname);
            break;
        case GROUP:
            qsort(mass, mass_count, sizeof(Student), CmpGroup);
            break;
    }
    FILE * output;
    if ((output = fopen(out, "w")) == NULL) {
        return OPEN_PROBLEM;
    }
    for (int i = 0; i < mass_count; i++) {
        fprintf(output ,"%d %s %s %s %s\n", (mass)[i].id, (mass)[i].name, (mass)[i].surname, (mass)[i].group, (mass)[i].rating);
    }
    fclose(output);
    return OK;

}


int main(int argc, char ** argv) {
    free(NULL);
    char * in;
    char * out;
    Student * mass;
    int mass_count;
    float medium_rate;
    int max_current_count;
    if (GetArgs(argc, argv, &in, &out)) {
        printf("incorrect arguments");
        return INCORRECT_ARGUMENTS;
    }
    statuses status = MassFulling(&mass, "in.txt", &mass_count, &medium_rate, &max_current_count);
    switch(status) {
        case MEM_PROBLEM:
            printf("memory trouble");
            break;
        case INCORRECT_ARGUMENTS:
            printf("incorrect arguemtns");
            break;
        case OPEN_PROBLEM:
            printf("open problem");
            break;
        case OK:
            printf("Доступные команды: FindId, FindName, FindSurname, FindGroup, SortId, "); 
            printf("SortName, SortSurname, SortGroup, Best, Quit\n");
            char command[15];
            unsigned int id;
            int ans_status;
            char input[max_current_count];
            while (1) {
                printf("Введите команду:\n");
                scanf("%s", command);
                if (strcmp(command, "Quit") == 0) {
                    status = OK;
                    break;
                }
                else if (strcmp(command, "FindID") == 0) {
                    printf("Введите ID\n");
                    if (scanf("%d", &id) == -1) {
                        printf("incorrect input\n");
                    }
                    ans_status = FinderID(mass, mass_count, id, out);
                    switch(ans_status) {
                        case OPEN_PROBLEM:
                            printf("open problem");
                            status = OPEN_PROBLEM;
                            break;
                        case INCORRECT_ARGUMENTS:
                            printf("incorrect input");
                            status = INCORRECT_ARGUMENTS;
                            break;
                    }
                }
                else if (strcmp(command, "FindName") == 0) {
                    printf("Введите Name\n");
                    scanf("%s", input);
                    ans_status = Finder(mass, mass_count, input, out, NAME);
                    if (ans_status == OPEN_PROBLEM) {
                        printf("open problem");
                        break;
                    }
                    else if (ans_status == INCORRECT_ARGUMENTS) {
                        printf("incorrect input\n");
                    }
                }
                else if (strcmp(command, "FindSurname") == 0) {
                    printf("Введите Surname\n");
                    scanf("%s", input);
                    ans_status = Finder(mass, mass_count, input, out, SURNAME);
                    if (ans_status == OPEN_PROBLEM) {
                        printf("open problem");
                        break;
                    }
                    else if (ans_status == INCORRECT_ARGUMENTS) {
                        printf("incorrect input\n");
                    }
                }
                else if (strcmp(command, "FindGroup") == 0) {
                    printf("Введите Group\n");
                    scanf("%s", input);
                    ans_status = Finder(mass, mass_count, input, out, GROUP);
                    if (ans_status == OPEN_PROBLEM) {
                        printf("open problem");
                        break;
                    }
                    else if (ans_status == INCORRECT_ARGUMENTS) {
                        printf("incorrect input\n");
                    }
                }
                else if (strcmp(command, "Best") == 0) {
                    ans_status = Best(mass, mass_count, medium_rate, 0.0001, out);
                    if (ans_status == OPEN_PROBLEM) {
                        printf("open problem");
                        break;
                    }
                    else if (ans_status == INCORRECT_ARGUMENTS) {
                        printf("incorrect input\n");
                    }
                }
                else if (strcmp(command, "SortId") == 0) {
                    ans_status = SortToFile(mass, mass_count, ID, out);
                    if (ans_status == OPEN_PROBLEM) {
                        printf("open problem");
                        break;
                    }


                }
                else if (strcmp(command, "SortName") == 0) {
                    ans_status = SortToFile(mass, mass_count, NAME, out);
                    if (ans_status == OPEN_PROBLEM) {
                        printf("open problem");
                        break;
                    }
                    

                }
                else if (strcmp(command, "SortSurname") == 0) {
                    ans_status = SortToFile(mass, mass_count, SURNAME, out);
                    if (ans_status == OPEN_PROBLEM) {
                        printf("open problem");
                        break;
                    }
                    

                }
                else if (strcmp(command, "SortGroup") == 0) {
                    ans_status = SortToFile(mass, mass_count, GROUP, out);
                    if (ans_status == OPEN_PROBLEM) {
                        printf("open problem");
                        break;
                    }
                    

                }
                else {
                    printf("incorrect command\n");
                }
            }
    }
    for (int i = 0; i < mass_count; i++) {
        free(mass[i].name);
        free(mass[i].surname);
        free(mass[i].group);
        free(mass[i].rating);
    }
    free(mass);
    return status;
}