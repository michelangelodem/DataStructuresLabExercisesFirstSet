#include "HeightLevel.h"

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