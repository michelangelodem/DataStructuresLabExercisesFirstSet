#include "OrderLevel.h"

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
