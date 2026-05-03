#include "HeightLevel.h"

void printLevels(const Node* root) {
    if (root == NULL) {
        return;
    }

    Queue q;
    if (!initializeQueue(&q)) {
        fprintf(stderr, "ERROR: Failed to initialize queue in printLevels\n");
        return;
    }
    
    if (!enqueue(&q, (Node*)root)) {
        fprintf(stderr, "ERROR: Failed to enqueue root node\n");
        freeQueue(&q);
        return;
    }

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
            if (!enqueue(&q, currentNode->left)) {
                fprintf(stderr, "ERROR: Failed to enqueue left child\n");
            }
            nodesInNextLevel++;
        }
        if (currentNode->right) {
            if (!enqueue(&q, currentNode->right)) {
                fprintf(stderr, "ERROR: Failed to enqueue right child\n");
            }
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