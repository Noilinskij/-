#include <stdio.h>
#include <stdlib.h>
#include <memory.h>


typedef enum statuses {
    OK,
    INCORRECT_ARGUMENTS,
    MEM_TROUBLE
} statuses;

typedef enum kOpts {
    OPT_L,
    OPT_R,
    OPT_U,
    OPT_N,
    OPT_C
} kOpts;


int getArgs(int argc, kOpts * option, char ** argv);
int SizeOfStr (char * s);
char * ReverseStr (char * s);
char * TaskU (char * s);
char * TaskN (char * s);
int UnsignedIntСhecker(char * s);
char * TaskC (int argc, char ** argv);

int getArgs(int argc, kOpts * option, char ** argv) {
    if (argc < 3) {
        return INCORRECT_ARGUMENTS;
    }
    if (argv[1][2] == 0 && (argv[1][0] == '-' || argv[1][0] == '/')) {
        if (argv[1][1] == 'l') {
            *option = OPT_L;
            return OK;
        }
        else if (argv[1][1] == 'r') {
            *option = OPT_R;
            return OK;
        }
        else if (argv[1][1] == 'u') {
            *option = OPT_U;
            return OK;
        }
        else if (argv[1][1] == 'n') {
            *option = OPT_N;
            return OK;
        }
        else if (argc >= 5 && argv[1][1] == 'c' && !(UnsignedIntСhecker(argv[3]))) {
            *option = OPT_C;
            return OK;
        }
        return INCORRECT_ARGUMENTS;
    }
    return INCORRECT_ARGUMENTS;
}

int SizeOfStr (char * s) {
    int ans = 0;
    for (int i = 0; s[i] != 0; i++) {
        ans = i + 1;
    }
    return ans;
}

char * ReverseStr (char * s) {
    int len = SizeOfStr(s);
    char * ans = (char *) malloc(len + 1);
    if (ans == NULL) {
        return NULL;
    }
    for (int i = len - 1; i >= 0; i--) {
        ans[len - 1 - i] = s[i];
    }
    ans[len] = 0;
    return ans;
}

char * TaskU (char * s) {
    int len = SizeOfStr(s);
    char * ans = (char *) malloc(len + 1);
    if (ans == NULL) {
        return NULL;
    }
    for (int i = 0; i < len; i++) {
        ans[i] = s[i];
        if (i % 2 != 0 && (s[i] >= 'a' && s[i] <= 'z')) {
            ans[i] += 'A' - 'a';
        }
    }
    return ans;
}

char * TaskN (char * s) {
    int len = SizeOfStr(s);
    int current_num = 0;
    int current_letter = 0;
    int current_special = 0;
    char * ans = (char *) malloc(len + 1);
    if (ans == NULL) {
        return NULL;
    }
    char * letters = (char *) malloc(len + 1);
    if (letters == NULL) {
        return NULL;
    }
    char * specials = (char *) malloc(len + 1);
    if (specials == NULL) {
        return NULL;
    }
    for (int i = 0; i < len; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            ans[current_num++] = s[i];
        }
        else if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) {
            letters[current_letter++] = s[i];
        } 
        else {
            specials[current_special++] = s[i];
        }
    }
    // memcpy копирует в память на которую указывает ans + current_num память, на которую указывает letters( current_letter байт)
    memcpy(ans + current_num, letters, current_letter);
    memcpy(ans + current_num + current_letter, specials, current_special);
    ans[len] = 0;
    free(letters);
    free(specials);
    return ans;

}

int UnsignedIntСhecker(char * s) {
    for (int i = 0; s[i] != 0; i++) {
        if (s[i] >= '0' && s[i] <= '9') continue;
        else return INCORRECT_ARGUMENTS;
    }
    return OK;
}


char * TaskC (int argc, char ** argv) {
    int str_count = argc - 4;
    int seed = atoi(argv[3]);
    srand(seed);
    int random_mass[str_count];
    int len = 0;
    for (int i = 0; i < str_count; i++) {
        random_mass[i] = i;
        len += SizeOfStr(argv[i +str_count]);
    }
    int j = 0;
    int tmp = 0;
    // алгорит Фишера-Йетса с тусованием карт
    for (int i = str_count - 1; i > 0; i--) {
        j = rand() % i;
        tmp = random_mass[i];
        random_mass[i] = random_mass[j];
        random_mass[j] = tmp;
    }
    char * ans = (char *) malloc(len + 1);
    int count = 0;
    for (int i = 0; i < str_count; i++) {
        for (int j = 0; argv[str_count + random_mass[i]][j] != 0; j++) {
            ans[count] = argv[str_count + random_mass[i]][j];
            count++;
        }
    }
    return ans;
}