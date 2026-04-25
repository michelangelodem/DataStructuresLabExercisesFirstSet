#include "queue.h"

void initializeQueue(Queue* q) {
    q->data = (Node**)malloc(sizeof(Node*) * MAX_SIZE);
    q->front = 0;
    q->back = -1;
}

void enqueue(Queue* q, Node* n) {
    if (q->back < MAX_SIZE - 1) {
        q->data[++(q->back)] = n;
    }
}

void dequeue(Queue* q) {
    if (q->front <= q->back) {
        q->front++;
    }
}

Node* peek(const Queue* q) {
    if (q->front <= q->back) {
        return q->data[q->front];
    }
    return NULL;
}

void freeQueue(Queue* q) {
    free(q->data);
    q->data = NULL;
    q->front = 0;
    q->back = -1;
}