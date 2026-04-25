#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

int* createSortedArray(int size);
int* createIntArray(int size);
void freeTree(Node* root);

Node* createNode(int key);
Node* createTree(int size, int index, int arr[]);
Node* sortedArrayToBST(int arr[], int start, int end);

#endif