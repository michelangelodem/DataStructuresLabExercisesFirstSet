#include "tree.h"

int* createIntArray(int size) {
    if (size <= 0) {
        return NULL;
    }
    int* arr = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100; 
    }
    return arr;
}

void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}   

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* createTree(int size, int index, int arr[]) {
    Node* node = NULL;
    if (index < size) {
        node = createNode(arr[index]);
        node->left = createTree(size, 2 * index + 1, arr);
        node->right = createTree(size, 2 * index + 2, arr);
    } 
    return node;
}

int* createSortedArray(int size) {
    int* arr = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        int val = rand() % 100; 
        if (i > 0 && val <= arr[i - 1]) {
            val = arr[i - 1] + 1 + rand() % 10; 
        } 
        arr[i] = val;
    }
    return arr;
}

Node* sortedArrayToBST(int arr[], int start, int end) {
    if (start > end) {
        return NULL;
    }
    
    int mid = start + (end - start) / 2;
    Node* node = createNode(arr[mid]);
    
    node->left = sortedArrayToBST(arr, start, mid - 1);
    node->right = sortedArrayToBST(arr, mid + 1, end);
    
    return node;
}