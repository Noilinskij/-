#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct queue {
    Node* front;
    Node* rear;

} queue;

void initqueue(queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

int push(queue* q, int value) {
    if (q == NULL) {
        return -1;
    }
    Node* newnode = (Node*) malloc(sizeof(Node));
    if (newnode == NULL) {
        return -1;
    }
    newnode->value = value;
    newnode->next = NULL;
    if (q->front == NULL) {
        q->front = newnode;
        q->rear = newnode;
        return 0;
    }
    q->rear->next = newnode;
    q->rear = newnode;
    return 0;
}

int pop(queue* q, int* ans) {
    if (q == NULL) {
        return -1;
    }
    if (q->front == NULL) {
        return -1;
    }
    Node* tmp = q->front;
    *ans = q->front->value;
    q->front = q->front->next;
    free(tmp);
    return 0;
}

int subqueue(queue* initial, size_t without, queue** result) {
    Node* current = initial->front;
    int count = 0;
    while(current) {
        count++;
        push(*result, current->value);
        current = current->next;
    }
    int count_res;
    if (without < count) {
        count_res = count - without;
    }
    else {
        count_res = 0;
    }
    current = (*result)->front;
    for (int i = 1; i < count_res; i++) {
        current = current->next;
    }
    Node* tmp = current;
    current = current->next;
    tmp->next = NULL;
    while(current) {
        tmp = current;
        current = current->next;
        free(tmp);
    }
    if (count_res == 0 ) {
        free((*result)->front);
        (*result)->front = NULL;
        (*result)->rear = NULL;
    }
    return 0;

}

int main() {
    queue* q = (queue*) malloc(sizeof(queue));
    initqueue(q);
    push(q, 2);
    push(q, 3);
    push(q, 1);
    queue* q2 = (queue*) malloc(sizeof(queue));
    initqueue(q2);
    subqueue(q, 2, &q2);
    int ans;
    while(pop(q2, &ans) != -1) {
        printf("%d ", ans);
    }

}