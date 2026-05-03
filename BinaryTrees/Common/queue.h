#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

#define MAX_SIZE 100

typedef struct Queue {
    Node** data; 
    int front;
    int back;
    int count;
} Queue;


int initializeQueue(Queue* q);
int enqueue(Queue* q, Node* n);
int dequeue(Queue* q);
Node* peek(const Queue* q);
void freeQueue(Queue* q);
#endif