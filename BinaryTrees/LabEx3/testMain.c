#include <stdio.h>
#include <stdlib.h>
#include "OrderLevel.h"

// =================================================================================
// =============================  TEST BINARY TREE TRAVERSAL  =====================
// =================================================================================

void runTests(Node* root) {
    printf("\nPre Order Traversal:\n");
    printPreOrder(root);
    printf("\n");

    printf("\nPost Order Traversal:\n");
    printPostOrder(root);
    printf("\n");

    printf("\nLevel Order Traversal:\n");
    printLevelOrder(root);
    printf("\n");
}

int main(void) {
    Node* root = NULL; // Initialize root to NULL
    runTests(root);

    
    freeTree(root);
    return 0;
}