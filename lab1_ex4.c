#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


typedef enum kOpts{
    OPT_D,
    OPT_I,
    OPT_S,
    OPT_A
} kOpts;


int getOpts(int argc, char ** argv, kOpts *opt, char ** in, char ** out);
int HandlerOptD(char * in, char * out);
int HandlerOptI(char * in, char * out);
int HandlerOptS(char * in, char * out);
char * AsciitoHex(int number);


int getOpts(int argc, char ** argv, kOpts *opt, char ** in, char ** out){
    if (argc == 3 && strlen(argv[1]) == 2 && (argv[1][0] == '/' || argv[1][0] == '-')){
        *in = argv[2];
        *out = malloc(strlen("out_") + strlen(*in) + 1);
        if (*out == NULL){
            printf("Memory trouble");
            return 1;
        }
        strcpy(*out, "out_");
        strcat(*out, *in);
        if (argv[1][1] == 'd'){
            *opt = OPT_D;
            return 0;
        }
        if (argv[1][1] == 'i'){
            *opt = OPT_I;
            return 0;
        }
        if (argv[1][1] == 's'){
            *opt = OPT_S;
            return 0;
        }
        if (argv[1][1] == 'a'){
            *opt = OPT_A;
            return 0;
        }
        


    }
    else if (argc == 4 && strlen(argv[1]) == 3 && (argv[1][0] == '/' || argv[1][0] == '-') && argv[1][1] == 'n'){
        *in = argv[2];
        *out = argv[3];
        if (argv[1][2] == 'd'){
            *opt = OPT_D;
            return 0;
        }
        if (argv[1][2] == 'i'){
            *opt = OPT_I;
            return 0;
        }
        if (argv[1][2] == 's'){
            *opt = OPT_S;
            return 0;
        }
        if (argv[1][2] == 'a'){
            *opt = OPT_A;
            return 0;
        }

    }
    return 1;
}

int HandlerOptD(char * in, char * out) {
    FILE * input;
    FILE * output;
    char current;
    if ((input = fopen(in, "r")) == NULL) {
        printf("The input file could not be opened");
        return 1;
    }
    else if ((output = fopen(out, "w")) == NULL) { // закрыть файл
        printf("The output file could not be opened");
        return 1;

    }
    while((current = fgetc(input)) != EOF){
        if (!isdigit(current)){
            fputc(current, output);
        }
    }
    fclose(input);
    fclose(output);
    free(out);
    return 0;

}

int HandlerOptI(char * in, char * out) {
    FILE * input;
    FILE * output;
    char current;
    int sums = 0;
    if ((input = fopen(in, "r")) == NULL) {
        printf("The input file could not be opened");
        return 1;
    }
    else if ((output = fopen(out, "w")) == NULL) {
        printf("The output file could not be opened");
        return 1;

    }
    while((current = fgetc(input)) != EOF){
        if (isalpha(current)){
            sums++;
        }
        else if(current == '\n'){
            fprintf(output, "%d", sums);
            fputc('\n', output);
            sums = 0;
        }
    }
    fprintf(output, "%d", sums);
    fclose(input);
    fclose(output);
    free(out);
    return 0;
}

int HandlerOptS(char * in, char * out){
    FILE * input;
    FILE * output;
    char current;
    int sums = 0;
    if ((input = fopen(in, "r")) == NULL) {
        printf("The input file could not be opened");
        return 1;
    }
    else if ((output = fopen(out, "w")) == NULL) {
        printf("The output file could not be opened");
        return 1;

    }
    while((current = fgetc(input)) != EOF){
        if (!isalpha(current) && !isdigit(current) && current != ' ' && current != '\n'){
            sums++;
        }
        else if(current == '\n'){
            sums++;
            fprintf(output, "%d", sums);
            fputc('\n', output);
            sums = 0;
        }
    }
    sums++;
    fprintf(output, "%d", sums);
    fclose(input);
    fclose(output);
    free(out);
    return 0;
}

int HandlerOptA(char * in, char * out) {
    FILE * input;
    FILE * output;
    char current;
    int sums = 0;
    if ((input = fopen(in, "r")) == NULL) {
        printf("The input file could not be opened");
        return 1;
    }
    else if ((output = fopen(out, "w")) == NULL) {
        printf("The output file could not be opened");
        return 1;

    }
    while((current = fgetc(input)) != EOF){
        if (!isdigit(current) && current != '\n') {
            char * x = AsciitoHex(current);
            if (x != NULL) { 
                fprintf(output,"%s", x);
                free(x);
            }
            else{
                return 1;
            }
        }
        else if(current == '\n') {
            fputc('\n', output);
        }
        else fprintf(output, "%c", current);
    }
    fclose(input);
    fclose(output);
    free(out);
    return 0;

}

char * AsciitoHex(int number) {
    int count = 1;
    int currentOsn = 1;
    int currentAns = 0;
    char *ans = malloc(sizeof(char) * 2 + 1);
    if (ans == NULL){
        printf("Memory trouble");
        return NULL;
    }
    ans[0] = '0';
    ans[1] = '0';
    ans[2] = '\0';
    while(currentOsn <= number){
        currentOsn *= 16;
        count++;
    }
    count--;
    currentOsn /= 16;
    while (number > 0){
        while(number >= currentOsn) {
            number -= currentOsn;
            currentAns += 1;
        }
        if (currentAns < 10) ans[2 - count] = '0' + currentAns;
        else{
            switch(currentAns){
                case 10:
                    ans[2 - count] = 'A';
                    break;
                case 11:
                    ans[2 - count] = 'B';
                    break;
                case 12:
                    ans[2 - count] = 'C';
                    break;
                case 13:
                    ans[2 - count] = 'D';
                    break;
                case 14:
                    ans[2 - count] = 'E';
                    break;
                case 15:
                    ans[2 - count] = 'F';
                    break;

            }
        }
        count--;
        currentAns = 0;
        currentOsn /= 16;
    }
    while(count > 0){
        ans[2 - count] = '0';
        count--;
    }

    return ans;

}



int main(int argc, char ** argv){
    kOpts opt = 0;
    char * in;
    char * out;
    int (*handlers[4])(char *, char *) = {
        HandlerOptD,
        HandlerOptI,
        HandlerOptS,
        HandlerOptA

    };
    if (getOpts(argc, argv, &opt, &in, &out)){
        printf("incorrect arguments");
        return 1;

    }
    if (!handlers[opt](in, out)) return 0;
    else return 1;

}