#include "lab3_ex10.h"

Node * CreateNode(char * info) {
    Node * node = (Node *) malloc(sizeof(Node));
    node->child_count = 0;
    node->child_size = 0;
    node->child = NULL;
    node->info = (char *) malloc(strlen(info) + 1);
    if (node->info == NULL) {
        return NULL;
    }
    strcpy(node->info, info);
    int count = 0;
    return node;
}

Node* MakeTree(char *str, int *count) {
    int current_size = 0;
    int info_size = 0;
    char * info = NULL;
    char * tmp = NULL;
    // читаем info для текущего
    while (str[*count] != '(' && str[*count] != 0 && str[*count] != ')' && str[*count] != ',') {
        current_size++;
        if (current_size >= info_size - 1) {
            info_size  = current_size * 2;
            tmp = (char *)realloc(info, info_size);
            if (tmp == NULL) {
                free(info);
                return NULL;
            }
            info = tmp;
        }
        info[current_size - 1] = str[*count];
        (*count)++;
    }
    info[current_size] = 0;
    Node *root = CreateNode(info);
    free(info);
    if (root == NULL) {
        return NULL;
    }
    Node ** tmp2;
    // если это node с детьми, то продолжаем строить поддерево, 
    // где он корень, если рядовой, то возвращаем
    if (str[*count] == '(') {
        (*count)++;
        while (str[*count] != 0 && str[*count] != ')') {
            if (str[*count] == ',') {
                (*count)++;
            } 
            else {
                Node *child = MakeTree(str, count);
                if (child == NULL) {
                    return NULL;
                }
                root->child_count++;
                if (root->child_count >= root->child_size) {
                    root->child_size = root->child_count * 2;
                    Node **tmp2 = (Node **)realloc(root->child, 
                    root->child_size * sizeof(Node *));
                    if (tmp2 == NULL) {
                        return NULL;
                    }
                    root->child = tmp2;
                }
                
                root->child[root->child_count - 1] = child;
            }
        }
        if (str[*count] == ')') {
            (*count)++;
        }
    }
    return root;
}

void PrintTree(Node* root, int depth, FILE * out) {
    for (int i = 0; i < depth; i++) {
        fprintf(out, " ");
    }
    fprintf(out, "%s\n", root->info);
    for (int i = 0; i < root->child_count; i++) {
        if (root->child == NULL) {
            continue;
        }
        PrintTree(root->child[i], depth + 1, out);
    }
}

void FreeTree(Node * root) {
    for (int i = 0; i < root->child_count; i++) {
        FreeTree(root->child[i]);
    }
    free(root->child);
    free(root->info);
    free(root);
}


int main(int argc, char ** argv) {
    if (argc != 3) {
        printf("incorrect arguments");
        return INCORRECT_ARGUMENTS;
    }
    if (strcmp(argv[1], argv[2]) == 0) {
        printf("incorrect arguments");
        return INCORRECT_ARGUMENTS;
    }
    FILE * in;
    FILE * out;
    if ((in = fopen(argv[1], "r")) == NULL) {
        printf("open problem");
        return OPEN_PROBLEM;
    }
    if ((out = fopen(argv[2], "w")) == NULL) {
        fclose(in);
        printf("open problem");
        return OPEN_PROBLEM;
    }
    char * current_str;
    int count_for_func = 0;
    char * tmp;
    Node * root;
    char current;
    int size_str = 0;
    int count = 0;
    while ((current = getc(in)) != EOF) {
        count++;
        if (count >= size_str) {
            size_str = count * 2 + 1;
            tmp = (char *) realloc(current_str, size_str);
            if (tmp == NULL) {
                fclose(in);
                fclose(out);
                FreeTree(root);
                free(current_str);
                printf("memory trouble");
                return MEM_TROUBLE;
            }
            current_str = tmp;
        }
        if (current != '\n') {
            current_str[count - 1] = current;
        }
        else {
            current_str[count] = 0;
            root = MakeTree(current_str, &count_for_func);
            if (root == NULL) {
                fclose(in);
                fclose(out);
                free(current_str);
                printf("memory trouble");
                return MEM_TROUBLE;
            }
            PrintTree(root, 0, out);
            fprintf(out, "---------------------------------------\n");
            FreeTree(root);
            memset(current_str, 0, size_str);
            count = 0;
            count_for_func = 0;

        }
    }
    if (current_str[0]) {
        current_str[count] = 0;
            root = MakeTree(current_str, &count_for_func);
            if (root == NULL) {
                fclose(in);
                fclose(out);
                free(current_str);
                printf("memory trouble");
                return MEM_TROUBLE;
            }
            PrintTree(root, 0, out);
            fprintf(out, "---------------------------------------\n");
            FreeTree(root);
            memset(current_str, 0, size_str);
            count = 0;
            count_for_func = 0;
    }
    free(current_str);
    fclose(in);
    fclose(out);
    return OK;


}