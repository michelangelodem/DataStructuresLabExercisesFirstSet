#include <stdio.h>
#include <stdlib.h>
#include "BinaryTreeSearch.h"

void printResults(Node* searchResult, int key) {
    printf("\n");
    if (searchResult != NULL) {
        printf("Key %d found in the BST.\n", key);
    } else {
        printf("Key %d not found in the BST.\n", key);
    }
}

int main(void) {
    int size = 10;
    int* sortedArray = createSortedArray(size);
    if (sortedArray == NULL) {
        fprintf(stderr, "Failed to allocate array.\n");
        return 1;
    }

    Node* root = sortedArrayToBST(sortedArray, 0, size - 1);
    if (root == NULL) {
        fprintf(stderr, "Failed to create BST.\n");
        free(sortedArray);
        return 1;
    }

    int keyToSearch = sortedArray[5];
    printResults(binaryTreeSearch(root, keyToSearch), keyToSearch);

    int keyToDelete = sortedArray[3];
    root = deleteNode(root, keyToDelete);
    printResults(binaryTreeSearch(root, keyToDelete), keyToDelete);
    
    root = insertNode(root, 42);
    printResults(binaryTreeSearch(root, 42), 42);
    
    free(sortedArray);
    freeTree(root);
    return 0;
}