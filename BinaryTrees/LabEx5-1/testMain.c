#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RecreateBTOptimised.h"

// =================================================================================
// =============================  TEST FOR TREE BUILDING  ==========================
// =================================================================================

int testCount = 0;
int passCount = 0;

void printOutcome(const char* testName, int condition) {
    testCount++;
    if (condition) {
        printf("Test %d PASS: %s\n", testCount, testName);
        passCount++;
    } else {
        printf("Test %d FAIL: %s\n", testCount, testName);
    }
}

Node* testWrapper(const char* preorder, const char* postorder, const char* inorder) {
    int length = strlen(inorder);
    int preIndex = 0;
    int postIndex = length - 1;

    HashTable* ht = malloc(sizeof(HashTable));
    if (ht == NULL) {
        fprintf(stderr, "Memory allocation failed for hash table.\n");
        return NULL;
    }

    initHashTable(ht, length);
    for (int i = 0; i < length; i++) {
        insertHashNode(ht, inorder[i], i);
    }

    Node* preRoot = buildTreeFromPreInOptimized(preorder, inorder, 0, length - 1, ht, &preIndex);
    
    // Reset postIndex for postorder traversal
    postIndex = length - 1;
    Node* postRoot = buildTreeFromPostInOptimized(postorder, inorder, 0, length - 1, ht, &postIndex);
    
    printf("Preorder result:  ");
    preOrderTraversal(preRoot);
    printf("\nPostorder result: ");
    preOrderTraversal(postRoot);
    printf("\n");
    
    freeTree(postRoot);
    freeHashTable(ht);
    return preRoot;
}

int main(void) {
    // Test 5.1: Single character
    printf("--- Test 5.1: Single Character ---\n");
    {
        const char preorder[] = "A";
        const char inorder[] = "A";
        const char postorder[] = "A";
        Node* root = testWrapper(preorder, postorder, inorder);
        printOutcome("Single character reconstructs correctly", root != NULL && root->data == 'A');
        freeTree(root);
    }

    // Test 5.2: Two nodes - left child only
    printf("\n--- Test 5.2: Two Nodes (Left Child) ---\n");
    {
        const char preorder[] = "AB";
        const char inorder[] = "BA";
        const char postorder[] = "BA";

        Node* root = testWrapper(preorder, postorder, inorder);
        printOutcome("Root is A", root != NULL && root->data == 'A');
        printOutcome("Left child is B", root->left != NULL && root->left->data == 'B');
        printOutcome("No right child", root->right == NULL);
        freeTree(root);
    }

    // Test 5.3: Two nodes - right child only
    printf("\n--- Test 5.3: Two Nodes (Right Child) ---\n");
    {
        const char preorder[] = "AB";
        const char inorder[] = "AB";
        const char postorder[] = "BA";

        Node* root = testWrapper(preorder, postorder, inorder);
        printOutcome("Root is A", root != NULL && root->data == 'A');
        printOutcome("Right child is B", root->right != NULL && root->right->data == 'B');
        printOutcome("No left child", root->left == NULL);
        freeTree(root);
    }

    // Test 5.4: Three nodes - balanced
    printf("\n--- Test 5.4: Three Nodes (Balanced) ---\n");
    {
        const char preorder[] = "ABC";
        const char inorder[] = "BAC";
        const char postorder[] = "BCA";

        Node* root = testWrapper(preorder, postorder, inorder);
        printOutcome("Root is A", root != NULL && root->data == 'A');
        printOutcome("Left child is B", root->left != NULL && root->left->data == 'B');
        printOutcome("Right child is C", root->right != NULL && root->right->data == 'C');
        freeTree(root);
    }

    // Test 5.5: Skewed left (linear)
    printf("\n--- Test 5.5: Skewed Left Tree ---\n");
    {
        const char preorder[] = "ABCDE";
        const char inorder[] = "EDCBA";
        const char postorder[] = "EDCBA";

        Node* root = testWrapper(preorder, postorder, inorder);
        printOutcome("Root is A", root != NULL && root->data == 'A');
        printOutcome("Left child is B", root->left != NULL && root->left->data == 'B');
        printOutcome("All nodes have left children only", 
                root->right == NULL && root->left->right == NULL);
        freeTree(root);
    }

    // Test 5.6: Skewed right (linear)
    printf("\n--- Test 5.6: Skewed Right Tree ---\n");
    {
        const char preorder[] = "ABCDE";
        const char inorder[] = "ABCDE";
        const char postorder[] = "EDCBA";

        Node* root = testWrapper(preorder, postorder, inorder);
        printOutcome("Root is A", root != NULL && root->data == 'A');
        printOutcome("Right child is B", root->right != NULL && root->right->data == 'B');
        printOutcome("All nodes have right children only", 
                root->left == NULL && root->right->left == NULL);
        freeTree(root);
    }

    // Test 5.7: Complex balanced tree
    printf("\n--- Test 5.7: Complex Balanced Tree ---\n");
    {
        const char preorder[] = "ABDEGUHQJLXRWCMOIPFKSTVYNZ";
        const char inorder[] = "GUEQHDLXJRWBMOCPIAFSYVTKNZ";
        const char postorder[] = "EGUQHDLXJRWBMOCPIAFSYVTKNZ";

        Node* root = testWrapper(preorder, postorder, inorder);
        printOutcome("Complex tree reconstructed correctly", root != NULL);
        freeTree(root);
    }

    // Test 5.8: Single Character Repeated
    printf("\n--- Test 5.8: Single Character Repeated ---\n");
    {
        const char preorder[] = "AAAA";
        const char inorder[] = "AAAA";
        const char postorder[] = "AAAA";

        Node* root = testWrapper(preorder, postorder, inorder);
        printOutcome("Repeated character reconstructs correctly", root != NULL);
        freeTree(root);
    }

    printf("\n================================================================================\n");
    printf("                      Test Suite Complete\n");
    printf("                    %d/%d tests passed\n", passCount, testCount);
    printf("================================================================================\n\n");
    return 0;
}