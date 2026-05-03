#include <stdio.h>
#include <stdlib.h>
#include "OrderLevel.h"

// =================================================================================
// =============================  TEST BINARY TREE TRAVERSAL  =====================
// =================================================================================

// Αφου καποια δέντρα βγαίνουν απο int arrays 
// που δημιουργούνται τυχαία με την createIntArray, 
// ειναι χρησιμο να έχουμε μια βοηθητική συνάρτηση για να τα τυπώνουμε 
// και να ελέγχουμε ότι όντως δημιουργούνται σωστά.

void printArr(int* arr, int size) {
    printf("Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    Node* root = NULL;

    printf("--- Test 3.1: Null Tree ---\n");
    {
        printf("Pre-order: ");
        printPreOrder(root);
        printf("\nLevel-order: ");
        printLevelOrder(root);
        printf("\nPost-order: ");
        printPostOrder(root);
    }
    printf("\n\n--- Test 3.2: Single Node Tree ---\n");
    {
        root = createNode(42);
        printf("Pre-order: ");
        printPreOrder(root);
        printf("\nLevel-order: ");
        printLevelOrder(root);
        printf("\nPost-order: ");
        printPostOrder(root);
        freeTree(root);
    }
    printf("\n\n--- Test 3.3: Complete Binary Tree ---\n");
    {
        int* arr = createIntArray(7);
        printArr(arr, 7);
        root = createTree(7, 0, arr);
        printf("Pre-order: ");
        printPreOrder(root);
        printf("\nLevel-order: ");
        printLevelOrder(root);
        printf("\nPost-order: ");
        printPostOrder(root);
        free(arr);
        freeTree(root);
    }
    printf("\n\n--- Test 3.4: Unbalanced Binary Tree ---\n");
    {
        root = createNode(1);
        root->right = createNode(2);
        root->right->right = createNode(3);
        printf("Pre-order: ");
        printPreOrder(root);
        printf("\nLevel-order: ");
        printLevelOrder(root);
        printf("\nPost-order: ");
        printPostOrder(root);
        freeTree(root);
    }
    printf("\n\n--- Test 3.5: Binary Search Tree ---\n");
    {
        int* arr = createSortedArray(7);
        printArr(arr, 7);
        root = sortedArrayToBST(arr, 0, 6);
        printf("Pre-order: ");
        printPreOrder(root);
        printf("\nLevel-order: ");
        printLevelOrder(root);
        printf("\nPost-order: ");
        printPostOrder(root);
        free(arr);
        freeTree(root);
    }
    return 0;
}