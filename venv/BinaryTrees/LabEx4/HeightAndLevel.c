#include <stdio.h>
#include <stdlib.h>
#include "../Common/tree.h"
#include "../Common/queue.h"

void printLevels(const Node* root) {
    if (root == NULL) {
        return;
    }

    Queue q;
    initializeQueue(&q);
    enqueue(&q, (Node*)root);

    int currentLevel = 0;
    int nodesInCurrentLevel = 1;
    int nodesInNextLevel = 0;

    while (q.front <= q.back) {
        Node* currentNode = peek(&q);
        if (currentNode == NULL) {
            break;
        }

        printf("Node: %d, level: %d\n", currentNode->data, currentLevel);
        dequeue(&q);

        if (currentNode->left) {
            enqueue(&q, currentNode->left);
            nodesInNextLevel++;
        }
        if (currentNode->right) {
            enqueue(&q, currentNode->right);
            nodesInNextLevel++;
        }

        if (--nodesInCurrentLevel == 0) {
            currentLevel++;
            nodesInCurrentLevel = nodesInNextLevel;
            nodesInNextLevel = 0;
        }
    }

    freeQueue(&q);
}

int getHeight(const Node* root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

void printHeight(const Node* root) {
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }
    int height = getHeight(root);
    printf("\nHeight of the tree: %d\n", height);
}

int main(void) {
    int size = 8;
    int* arr = createIntArray(size);
    if (arr == NULL) {
        fprintf(stderr, "Failed to allocate array.\n");
        return 1;
    }

    Node* root = createTree(size, 0, arr);
    if (root == NULL) {
        fprintf(stderr, "Failed to create binary tree.\n");
        free(arr);
        return 1;
    }

    free(arr);

    printLevels(root);
    printHeight(root);

    freeTree(root);
    return 0;
}