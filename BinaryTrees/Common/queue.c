#include "queue.h"

bool initializeQueue(Queue* q) {
    q->data = (Node**)malloc(sizeof(Node*) * MAX_SIZE);

    // Έλεγχος αν η μνήμη δεσμεύτηκε επιτυχώς
    if (q->data == NULL) {
        return false; 
    }

    q->front = 0;
    q->back = -1;
    q->count = 0;
    return true;
}

bool enqueue(Queue* q, Node* n) {
  if (q->count == MAX_SIZE) { return 0; }
    
    q->back = (q->back + 1) % MAX_SIZE; 
    
    // ΕΔΩ Η ΜΕΓΑΛΗ ΑΛΛΑΓΗ: 
    // Απλώς αποθηκεύουμε τη διεύθυνση μνήμης (τον δείκτη), ΟΧΙ ολόκληρο τον κόμβο!
    q->data[q->back] = n; 
    
    q->count++; 
    return true;
}

bool dequeue(Queue* q) {
    // Αν η ουρά είναι άδεια, επιστρέφει false
    if (q->count == 0) {
        return false; 
    }
    
    // Κυκλική αύξηση του front
    q->front = (q->front + 1) % MAX_SIZE; 
    q->count--; 
    return true;
}

Node* peek(const Queue* q) {
    if (q->count > 0) {
        // Τώρα η ουρά περιέχει δείκτες, άρα επιστρέφουμε κατευθείαν τον δείκτη
        return q->data[q->front]; 
    }
    return NULL;
}

bool freeQueue(Queue* q) {
    if (q->data != NULL) {
        free(q->data);
        q->data = NULL;
    }

    q->front = 0;
    q->back = -1;
    q->count = 0;
    return true;
}