#include <stdio.h>
#include <stdlib.h>
#include "../Common/tree.h"
#include "../Common/queue.h"

void printPreOrder(const Node* root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->data);
    printPreOrder(root->left);
    printPreOrder(root->right);
}

void printPostOrder(const Node* root) {
    if (root == NULL) {
        return;
    }
    printPostOrder(root->left);
    printPostOrder(root->right);
    printf("%d ", root->data);
}

void printLevelOrder(const Node* root) {
    if (root == NULL) {
        return;
    }

    Queue q;
    initializeQueue(&q);
    enqueue(&q, (Node*)root);

    while (q.front <= q.back) {
        Node* currentNode = peek(&q);
        if (currentNode == NULL) {
            break;
        }
        printf("%d ", currentNode->data);
        dequeue(&q);
        if (currentNode->left) {
            enqueue(&q, currentNode->left);
        }
        if (currentNode->right) {
            enqueue(&q, currentNode->right);
        }
    }

    freeQueue(&q);
}

int main(void) {
    int size = 8;
    int* arr = createIntArray(size);
    if (arr == NULL) {
        fprintf(stderr, "Failed to allocate input array.\n");
        return 1;
    }

    Node* root = createTree(size, 0, arr);
    if (root == NULL) {
        fprintf(stderr, "Failed to create binary tree.\n");
        free(arr);
        return 1;
    }

    free(arr);

    printf("\nPre Order Traversal:\n");
    printPreOrder(root);
    printf("\n");

    printf("\nPost Order Traversal:\n");
    printPostOrder(root);
    printf("\n");

    printf("\nLevel Order Traversal:\n");
    printLevelOrder(root);
    printf("\n");

    freeTree(root);
    return 0;
}