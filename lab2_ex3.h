#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int str_number;
    int symbol_number;
} values;

typedef enum statuses {
    OK,
    OPEN_PROBLEM,
    MEMORY_TROUBLE
} statuses;

typedef struct{
    statuses status;
    values * ans_for_file;
    int ans_for_file_len;
    char * filename;
    int count_files;
} finalyAns;

int SizeOfStr (char * s);
void calculate_prefix(char * str, int prefix_mass[], int len);
int StrInFile(char * str, char * file, int prefix_mass[], int len, values ** start);
int checkStr (char * s);
finalyAns * Task(char * str, ...);

finalyAns * Task(char * str, ...) {
    int len = SizeOfStr(str);
    va_list args;
    va_start(args, str);
    char * current = str;
    int prefix_mass[len];
    char * filename = "c";
    calculate_prefix(str, prefix_mass, len);
    finalyAns * answer = NULL;
    finalyAns * tmp = NULL;
    values * ans = NULL;
    // счетчик ответов в одном файле
    int count_ans = 0;
    // счетчик файлов
    int count_files = 0;
    while (1) {
        count_ans = 0;
        ans = NULL;
        filename = va_arg(args, char *);
        if (filename == NULL) {
            break;
        }
        count_files++;
        count_ans = StrInFile(str, filename, prefix_mass, len, &ans);
        // !!! сохранить ответ, если неудача realloc
        tmp = (finalyAns *) realloc(answer, count_files * sizeof(finalyAns));
        if (tmp == NULL) {
            return NULL;
        }
        answer = tmp;
        answer[count_files - 1].filename = filename;
        if (count_ans == OPEN_PROBLEM  && ans == NULL) {
            answer[count_files - 1].status = OPEN_PROBLEM;
            continue;
        }
        else if (count_ans == MEMORY_TROUBLE && ans == NULL) {
            answer[count_files - 1].status = MEMORY_TROUBLE;
            continue;
        }
        answer[count_files - 1].status = OK;
        answer[count_files - 1].ans_for_file = ans;
        answer[count_files - 1].ans_for_file_len = count_ans;

    }
    if (count_files > 0) {
        answer[0].count_files = count_files;
    }
    va_end(args);
    return answer;
    

}

void calculate_prefix(char * str, int prefix_mass[], int len) {
    prefix_mass[0] = 0;
    int prefix_len = 0;
    for (int i = 1; i < len; i++) {
        // если последний символ суффикса не совпадает с последним символом префикса,
        // то пытаемся найти совпадение с меньшей !возможной! длиной префикса
        if (prefix_len > 0 && str[i] != str[prefix_len]) {
            prefix_len = prefix_mass[prefix_len - 1];

        }
        // при совпадении увеличиваем длину совпадающего префикса
        if (str[prefix_len] == str[i]) {
            prefix_len++;
        }
        prefix_mass[i] = prefix_len;
    }

}

// кмп
int StrInFile(char * str, char * file, int prefix_mass[], int len, values ** start) {
    FILE * in;
    if ((in = fopen(file, "r")) == NULL) {
        return OPEN_PROBLEM;
    }
    char current;
    // кол-во \n в подстроке
    int count_n = checkStr(str);
    // совпадение строки и подстроки
    int count_sovpad = 0;
    // позиция в файле
    int count = 0;
    // номер строки
    int count_str_number = 1;
    // количество ответов
    int count_ans = 0;
    // начало вхождения
    int start_in = 0;
    values * ans;
    while ((current = fgetc(in)) != EOF) {
        count++;
        // если не совпадает, то двигаем подстроку 
        while (count_sovpad > 0 && current != str[count_sovpad]) {
            count_sovpad = prefix_mass[count_sovpad - 1];
        }
        // если совпдает, то увеличиваем совпадение строки и подстроки
        if (current == '\n') {
            count = 0;
            count_str_number++;
        }
        if (count_sovpad == 0 && current == str[count_sovpad]) {
            start_in = count;

        }
        if (current == str[count_sovpad]) {
            count_sovpad++;
        }
        // если нашли полное совпадение, то 
        if (count_sovpad == len) {
            count_ans++;
            ans = (values *)realloc(*start, sizeof(values) * count_ans);
            if (ans == NULL) {
                return MEMORY_TROUBLE;
            }
            *start = ans;
            ans[count_ans - 1].str_number = count_str_number - count_n;
            ans[count_ans - 1].symbol_number = start_in;
            count_sovpad = prefix_mass[count_sovpad - 1];
        }
    }
    fclose(in);
    return count_ans;
}

int checkStr (char * s) {
    int ans = 0;
    for (int i = 0; s[i] != 0; i++) {
        if (s[i] == '\n'){
            ans++;
        }
    }
    return ans;
}


int SizeOfStr (char * s) {
    int ans = 0;
    for (int i = 0; s[i] != 0; i++) {
        ans = i + 1;
    }
    return ans;
}