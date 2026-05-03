#include "queue.h"

int initializeQueue(Queue* q) {
    if (q == NULL) {
        fprintf(stderr, "ERROR: Queue pointer is NULL\n");
        return 0;
    }
    
    q->data = (Node**)malloc(sizeof(Node*) * MAX_SIZE);

    if (q->data == NULL) {
        fprintf(stderr, "ERROR: Failed to allocate memory for queue\n");
        return 0; 
    }

    q->front = 0;
    q->back = -1;
    q->count = 0;
    return 1;
}

int enqueue(Queue* q, Node* n) {
    if (q == NULL || q->data == NULL) {
        fprintf(stderr, "ERROR: Invalid queue\n");
        return 0;
    }
    
    if (q->count == MAX_SIZE) {
        fprintf(stderr, "ERROR: Queue overflow\n");
        return 0;
    }
    
    q->back = (q->back + 1) % MAX_SIZE; 
    q->data[q->back] = n; 
    
    q->count++; 
    return 1;
}

int dequeue(Queue* q) {
    if (q == NULL) {
        fprintf(stderr, "ERROR: Queue pointer is NULL\n");
        return 0;
    }

    if (q->count == 0) {
        fprintf(stderr, "ERROR: Queue underflow\n");
        return 0; 
    }

    q->front = (q->front + 1) % MAX_SIZE; 
    q->count--; 
    return 1;
}

Node* peek(const Queue* q) {
    if (q->count > 0) {
        return q->data[q->front]; 
    }
    return NULL;
}

void freeQueue(Queue* q) {
if (q->data != NULL) {
        free(q->data);
        q->data = NULL;
    }
    
    q->front = 0;
    q->back = -1;
    q->count = 0;
}