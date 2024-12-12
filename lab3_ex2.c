#include "lab3_ex2.h"

int InitVector(vector * vec, int size) {
    vec->size = size;
    vec->mass = (double *) calloc(size, sizeof(double));
    if (vec->mass == NULL) {
        return MEM_TROUBLE;
    }
    return OK;
}

int createVector(vector * vec, int size, ...) {
    if (InitVector(vec, size)) {
        return MEM_TROUBLE;
    }
    va_list args;
    va_start(args, size);
    for (int i = 0; i < size; i++) {
        vec->mass[i] = va_arg(args, double);
    }
    va_end(args);
    return OK;
    
}

double FirstNorm(vector vec, void * arg) {
    double ans = 0;
    for (int i = 0; i < vec.size; i++) {
        if (fabs(vec.mass[i]) > ans) {
            ans = fabs(vec.mass[i]);
        }
    }
    return ans;
}

double SecondNorm(vector vec, void * arg) {
    // явное приведение
    double p = *(double *) arg;
    double ans = 0;
    for (int i = 0; i < vec.size; i++) {
        ans += pow(fabs(vec.mass[i]), p);
    }
    return pow(ans, 1 / p);
}

double ThirdNorm(vector vec, void * arg) {
    vector * matrix = (vector *) arg;
    int size = vec.size;
    double help[size];
    double ans = 0;
    // идем по строкам матрицы
    for (int i = 0; i < size; i++) {
        help[i] = 0;
        for (int j = 0; j < size; j++) {
            help[i] += matrix[i].mass[j] * vec.mass[j];
        }
    }
    for (int i = 0; i < size; i++) {
        ans += help[i] * vec.mass[i];
    }
    return sqrt(ans);

}


finaly_ans Task(int n, int count, double eps, double p, vector * matrix, universal FirstNorm, 
universal SecondNorm, universal ThirdNorm, ...) {
    finaly_ans ans;
    ans.status = OK;
    if (p < 1) {
        ans.status = INCORRECT_ARGUMETNS;
        return ans;
    }
    va_list args;
    ans.ans1 = (vector *) calloc(1, sizeof(vector));
    if (ans.ans1 == NULL) {
        ans.status = MEM_TROUBLE;
        return ans;
    }
    ans.size1 = 1;
    ans.ans2 = (vector *) calloc(1, sizeof(vector));
    if (ans.ans2 == NULL) {
        free(ans.ans1);
        ans.status = MEM_TROUBLE;
        return ans;
    }
    ans.size2 = 1;
    ans.ans3 = (vector *) calloc(1, sizeof(vector));
    if (ans.ans3 == NULL) {
        free(ans.ans2);
        free(ans.ans3);
        ans.status = MEM_TROUBLE;
        return ans;
    }
    ans.size3 = 1;
    va_start(args, ThirdNorm);
    vector current;
    vector * tmp;
    for (int i = 0; i < count; i++) {
        current = va_arg(args, vector);
        if (current.size != n) {
            ans.status = INCORRECT_ARGUMETNS;
            return ans;
        }
        if (FirstNorm(current, NULL) - FirstNorm(ans.ans1[0], NULL) > eps) {
            ans.anses1 = 0;
            ans.ans1[ans.anses1] = current;

        }
        else if (fabs(FirstNorm(current, NULL) - FirstNorm(ans.ans1[0], NULL)) <= eps) {
            ans.anses1++;
            if (ans.anses1 >= ans.size1) {
                ans.size1 = ans.anses1 * 2;
                tmp = (vector *) realloc(ans.ans1, ans.size1 * sizeof(vector));
                if (tmp == NULL) {
                    free(ans.ans2);
                    free(ans.ans3);
                    ans.status = MEM_TROUBLE;
                    return ans;
                }
                ans.ans1 = tmp;
            }
            ans.ans1[ans.anses1] = current;

        }

        if (SecondNorm(current, &p) - SecondNorm(ans.ans2[0], &p) > eps) {
            ans.anses2 = 0;
            ans.ans2[ans.anses2] = current;

        }
        else if (fabs(SecondNorm(current, &p) - SecondNorm(ans.ans2[0], &p)) <= eps) {
            ans.anses2++;
            if (ans.anses2 >= ans.size2) {
                ans.size2 = ans.anses2 * 2;
                tmp = (vector *) realloc(ans.ans2, ans.size2 * sizeof(vector));
                if (tmp == NULL) {
                    free(ans.ans1);
                    free(ans.ans3);
                    ans.status = MEM_TROUBLE;
                    return ans;
                }
                ans.ans2 = tmp;
            }
            ans.ans2[ans.anses2] = current;

        }

        if (ThirdNorm(current, matrix) - ThirdNorm(ans.ans3[0], matrix) > eps) {
            ans.anses3 = 0;
            ans.ans3[ans.anses3] = current;

        }
        else if (fabs(ThirdNorm(current, matrix) - ThirdNorm(ans.ans3[0], matrix)) <= eps) {
            ans.anses3++;
            if (ans.anses3 >= ans.size3) {
                ans.size3 = ans.anses3 * 2;
                vector * tmp = (vector *) realloc(ans.ans3, ans.size3 * sizeof(vector));
                if (tmp == NULL) {
                    free(ans.ans1);
                    free(ans.ans2);
                    ans.status = MEM_TROUBLE;
                    return ans;
                }
                ans.ans3 = tmp;
            }
            ans.ans3[ans.anses3] = current;

        }

    }
    return ans;

}

int main() {
    vector vec;
    vector first;
    vector second;
    if (createVector(&vec, 2, 1.2, 1.3)) {
        printf("memory trouble");
        return MEM_TROUBLE;
    }
    if (createVector(&first, 2, 1.5, 0.1, 1.7)) {
        free(vec.mass);
        printf("memory trouble");
        return MEM_TROUBLE;
    }
    if (createVector(&second, 2, 0.1, 1.5)) {
        free(vec.mass);
        free(first.mass);
        printf("memory trouble");
        return MEM_TROUBLE;
    }
    int size = vec.size;
    vector * matrix = (vector *) malloc(sizeof(vector) * size);
    if (matrix == NULL) {
        free(vec.mass);
        free(first.mass);
        free(second.mass);
        printf("memory trouble");
        return MEM_TROUBLE;
    }
    for (int i = 0; i < size; i++) {
        matrix[i].mass = (double *) calloc(size, sizeof(double));
        if (matrix[i].mass == NULL) {
            for (int j = i - 1; j >= 0; j--) {
                free(matrix[j].mass);
            }
            free(matrix);
            free(vec.mass);
            free(first.mass);
            free(second.mass);
            printf("memory trouble");
            return MEM_TROUBLE;
        }
        matrix[i].mass[i] = 1.0;
    }

    finaly_ans ans;
    ans = Task(2, 3, 0.0001, 1.0, matrix, FirstNorm, SecondNorm, ThirdNorm, vec, first, second);
    switch(ans.status) {
        case OK:
            printf("anses1 %d:\n", ans.anses1 + 1);
            for (int i = 0; i <= ans.anses1; i++) {
                for (int j = 0; j < size; j++) {
                    printf("%f ", ans.ans1[i].mass[j]);
                }
                printf("\n");
            }
            printf("anses2 %d:\n", ans.anses2 + 1);
            for (int i = 0; i <= ans.anses2; i++) {
                for (int j = 0; j < size; j++) {
                    printf("%f ", ans.ans2[i].mass[j]);
                }
                printf("\n");
            }
            printf("anses3 %d:\n", ans.anses3 + 1);
            for (int i = 0; i <= ans.anses3; i++) {
                for (int j = 0; j < size; j++) {
                    printf("%f ", ans.ans3[i].mass[j]);
                }
                printf("\n");
            }
            break;
        case INCORRECT_ARGUMETNS:
            printf("incorrect arguments");
            break;
        case MEM_TROUBLE:
            free(matrix);
            free(vec.mass);
            free(first.mass);
            free(second.mass);
            printf("memory trouble");
            return MEM_TROUBLE;

    }
    for (int i = 0; i < size; i++) {
        free(matrix[i].mass);
    }
    free(matrix);
    free(vec.mass);
    free(first.mass);
    free(second.mass);
    free(ans.ans1);
    free(ans.ans2);
    free(ans.ans3);
    return ans.status;
    
}