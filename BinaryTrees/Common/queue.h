#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct Queue {
    Node** data; //Πινακας από δείκτες 
    int front;
    int back;
    int count;
} Queue;

bool initializeQueue(Queue* q);
bool enqueue(Queue* q, Node* n);
bool dequeue(Queue* q);
Node* peek(const Queue* q);
bool freeQueue(Queue* q);

#endif