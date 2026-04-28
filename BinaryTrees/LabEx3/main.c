#include <stdio.h>
#include <stdlib.h>
#include "OrderLevel.h"

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