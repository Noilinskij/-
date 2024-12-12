#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum statuses{
    OK,
    INCORRECT_ARGUMENTS,
    MEM_TROUBLE,
    OPEN_PROBLEM
} statuses;

typedef struct Node {
    char * info;
    struct Node ** child;
    int child_size;
    int child_count;
} Node;

Node * CreateNode(char * info);
Node* MakeTree(char *str, int *count);
void PrintTree(Node* root, int depth, FILE * out);
void FreeTree(Node * root);
