#include "queue.h"

void initializeQueue(Queue* q) {
    q->data = (Node**)malloc(sizeof(Node*) * MAX_SIZE);

    // Έλεγχος αν η μνήμη δεσμεύτηκε επιτυχώς
    if (q->data == NULL) {
        return 0; 
    }

    q->front = 0;
    q->back = -1;
    q->count = 0;
    return 1;
}

void enqueue(Queue* q, Node* n) {
  if (q->count == MAX_SIZE) { return 0; }
    
    q->back = (q->back + 1) % MAX_SIZE; 
    q->data[q->back] = n; 
    
    q->count++; 
    return 1;
}

void dequeue(Queue* q) {
    // Αν η ουρά είναι άδεια, επιστρέφει false
    if (q->count == 0) {
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