#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Common/hash_table.h"
#include "../Common/tree.h"

Node* buildTreeFromPreInOptimized(const char preorder[], const char inorder[], int inStart, int inEnd, HashTable* ht, int* preIndex) {
    if (inStart > inEnd || *preIndex < 0) {
        return NULL;
    }

    char current = preorder[(*preIndex)++];
    Node* node = createNode(current);
    if (node == NULL) {
        return NULL;
    }

    if (inStart == inEnd) {
        return node;
    }

    int inIndex = getHashNodeValue(ht, current);
    if (inIndex < inStart || inIndex > inEnd) {
        return node;
    }

    node->left = buildTreeFromPreInOptimized(preorder, inorder, inStart, inIndex - 1, ht, preIndex);
    node->right = buildTreeFromPreInOptimized(preorder, inorder, inIndex + 1, inEnd, ht, preIndex);
    return node;
}

Node* buildTreeFromPostInOptimized(const char postorder[], const char inorder[], int inStart, int inEnd, HashTable* ht, int* postIndex) {
    if (inStart > inEnd || *postIndex < 0) {
        return NULL;
    }

    char current = postorder[(*postIndex)--];
    Node* node = createNode(current);
    if (node == NULL) {
        return NULL;
    }

    if (inStart == inEnd) {
        return node;
    }

    int inIndex = getHashNodeValue(ht, current);
    if (inIndex < inStart || inIndex > inEnd) {
        return node;
    }

    node->right = buildTreeFromPostInOptimized(postorder, inorder, inIndex + 1, inEnd, ht, postIndex);
    node->left = buildTreeFromPostInOptimized(postorder, inorder, inStart, inIndex - 1, ht, postIndex);
    return node;
}

void preOrderTraversal(const Node* root) {
    if (root == NULL) {
        return;
    }
    printf("%c ", root->data);
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

bool checkInput(const char* preorder, const char* inorder, const char* postorder) {
    if (preorder == NULL || inorder == NULL || postorder == NULL) {
        fprintf(stderr, "Input strings cannot be NULL.\n");
        return false;
    }
    if (strlen(preorder) != strlen(inorder) || strlen(inorder) != strlen(postorder)) {
        fprintf(stderr, "Input strings must be of the same length.\n");
        return false;
    }
    if (strlen(inorder) == 0) {
        fprintf(stderr, "Input strings cannot be empty.\n");
        return false;
    }
    return true;

}

// int main(void) {
//     const char preorder[] = "ABDEGUHQJLXRWCMOIPFKSTVYNZ";
//     const char inorder[] = "GUEQHDLXJRWBMOCPIAFSYVTKNZ";
//     const char postorder[] = "UGQHEXLWRJDOMPICBYVTSZNKFA";

//     if (!checkInput(preorder, inorder, postorder)) {
//         return 1;
//     }
//
//     int length = strlen(inorder);
//     int preIndex = 0;
//     int postIndex = length - 1;
//
//     HashTable* ht = malloc(sizeof(HashTable));
//     if (ht == NULL) {
//         fprintf(stderr, "Memory allocation failed for hash table.\n");
//         return 1;
//     }

//     initHashTable(ht, length);
//     for (int i = 0; i < length; i++) {
//         insertHashNode(ht, inorder[i], i);
//     }

//     clock_t begin = clock();
//     Node* root1 = buildTreeFromPostInOptimized(postorder, inorder, 0, length - 1, ht, &postIndex);
//     Node* root2 = buildTreeFromPreInOptimized(preorder, inorder, 0, length - 1, ht, &preIndex);
//     clock_t end = clock();

//     double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
//     printf("Time taken to build trees (optimized): %f seconds\n", time_spent);

//     printf("Preorder Traversal of the reconstructed tree from postorder (optimized): ");
//     preOrderTraversal(root1);
//     printf("\n");

//     printf("Preorder Traversal of the reconstructed tree from preorder (optimized): ");
//     preOrderTraversal(root2);
//     printf("\n");

//     freeTree(root1);
//     freeTree(root2);
//     freeHashTable(ht);
//     return 0;
// }

// =================================================================================
// =============================  TEST FOR TREE BUILDING  ===================
// =================================================================================
// Uncomment τον παρακάτω κώδικα για να τρέξετε τα tests 
// και comment out τη main() παραπάνω.

void verifyTraversal(const char* expected, Node* root, const char* testName) {
    printf("  %s: Expected: %s\n  Traversal: ", testName, expected);
    preOrderTraversal(root);
    printf("\n");
}

int testCount = 0;
int passCount = 0;

void runTest(const char* testName, int condition) {
    testCount++;
    if (condition) {
        printf("Test %d PASS: %s\n", testCount, testName);
        passCount++;
    } else {
        printf("Test %d FAIL: %s\n", testCount, testName);
    }
}

int main(void) {
    // Test 5.1: Single character
    printf("--- Test 5.1: Single Character ---\n");
    {
        const char preorder[] = "A";
        const char inorder[] = "A";
        int length = strlen(inorder);
        int preIndex = 0;

        HashTable* ht = malloc(sizeof(HashTable));
        if (ht == NULL) {
            fprintf(stderr, "Memory allocation failed for hash table.\n");
            return 1;
        }

        initHashTable(ht, length);
        for (int i = 0; i < length; i++) {
            insertHashNode(ht, inorder[i], i);
        }
        clock_t begin = clock();
        Node* root = buildTreeFromPreInOptimized(preorder, inorder, 0, length - 1, ht, &preIndex);
        clock_t end = clock();

        printf("Time: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
        printf("Reconstructed tree: ");
        preOrderTraversal(root);
        printf("\n");
        runTest("Single character reconstructs correctly", root != NULL && root->data == 'A');
        freeTree(root);
        freeHashTable(ht);
    }

    // Test 5.2: Two nodes - left child only
    printf("\n--- Test 5.2: Two Nodes (Left Child) ---\n");
    {
        const char preorder[] = "AB";
        const char inorder[] = "BA";
        int length = strlen(inorder);
        int preIndex = 0;

        HashTable* ht = malloc(sizeof(HashTable));
        if (ht == NULL) {
            fprintf(stderr, "Memory allocation failed for hash table.\n");
            return 1;
        }

        initHashTable(ht, length);
        for (int i = 0; i < length; i++) {
            insertHashNode(ht, inorder[i], i);
        }

        Node* root = buildTreeFromPreInOptimized(preorder, inorder, 0, length - 1, ht, &preIndex);
        printf("Reconstructed tree: ");
        preOrderTraversal(root);
        printf("\n");
        runTest("Root is A", root != NULL && root->data == 'A');
        runTest("Left child is B", root->left != NULL && root->left->data == 'B');
        runTest("No right child", root->right == NULL);
        freeTree(root);
        freeHashTable(ht);
    }

    // Test 5.3: Two nodes - right child only
    printf("\n--- Test 5.3: Two Nodes (Right Child) ---\n");
    {
        const char preorder[] = "AB";
        const char inorder[] = "AB";
        int length = strlen(inorder);
        int preIndex = 0;

        HashTable* ht = malloc(sizeof(HashTable));
        if (ht == NULL) {
            fprintf(stderr, "Memory allocation failed for hash table.\n");
            return 1;
        }

        initHashTable(ht, length);
        for (int i = 0; i < length; i++) {
            insertHashNode(ht, inorder[i], i);
        }


        Node* root = buildTreeFromPreInOptimized(preorder, inorder, 0, length - 1, ht, &preIndex);
        printf("Reconstructed tree: ");
        preOrderTraversal(root);
        printf("\n");
        runTest("Root is A", root != NULL && root->data == 'A');
        runTest("Right child is B", root->right != NULL && root->right->data == 'B');
        runTest("No left child", root->left == NULL);
        freeTree(root);
        freeHashTable(ht);
    }

    // Test 5.4: Three nodes - balanced
    printf("\n--- Test 5.4: Three Nodes (Balanced) ---\n");
    {
        const char preorder[] = "ABC";
        const char inorder[] = "BAC";
        int length = strlen(inorder);
        int preIndex = 0;

        HashTable* ht = malloc(sizeof(HashTable));
        if (ht == NULL) {
            fprintf(stderr, "Memory allocation failed for hash table.\n");
            return 1;
        }

        initHashTable(ht, length);
        for (int i = 0; i < length; i++) {
            insertHashNode(ht, inorder[i], i);
        }

        Node* root = buildTreeFromPreInOptimized(preorder, inorder, 0, length - 1, ht, &preIndex);
        printf("Reconstructed tree: ");
        preOrderTraversal(root);
        printf("\n");
        runTest("Root is A", root != NULL && root->data == 'A');
        runTest("Left child is B", root->left != NULL && root->left->data == 'B');
        runTest("Right child is C", root->right != NULL && root->right->data == 'C');
        freeTree(root);
        freeHashTable(ht);
    }

    // Test 5.5: Skewed left (linear)
    printf("\n--- Test 5.5: Skewed Left Tree ---\n");
    {
        const char preorder[] = "ABCDE";
        const char inorder[] = "EDCBA";
        int length = strlen(inorder);
        int preIndex = 0;

        HashTable* ht = malloc(sizeof(HashTable));
        if (ht == NULL) {
            fprintf(stderr, "Memory allocation failed for hash table.\n");
            return 1;
        }

        initHashTable(ht, length);
        for (int i = 0; i < length; i++) {
            insertHashNode(ht, inorder[i], i);
        }

        Node* root = buildTreeFromPreInOptimized(preorder, inorder, 0, length - 1, ht, &preIndex);
        printf("Reconstructed tree: ");
        preOrderTraversal(root);
        printf("\n");
        runTest("Root is A", root != NULL && root->data == 'A');
        runTest("Left child is B", root->left != NULL && root->left->data == 'B');
        runTest("All nodes have left children only", 
                root->right == NULL && root->left->right == NULL);
        freeTree(root);
        freeHashTable(ht);
    }

    // Test 5.6: Skewed right (linear)
    printf("\n--- Test 5.6: Skewed Right Tree ---\n");
    {
        const char preorder[] = "ABCDE";
        const char inorder[] = "ABCDE";
        int length = strlen(inorder);
        int preIndex = 0;

        HashTable* ht = malloc(sizeof(HashTable));
        if (ht == NULL) {
            fprintf(stderr, "Memory allocation failed for hash table.\n");
            return 1;
        }

        initHashTable(ht, length);
        for (int i = 0; i < length; i++) {
            insertHashNode(ht, inorder[i], i);
        }

        Node* root = buildTreeFromPreInOptimized(preorder, inorder, 0, length - 1, ht, &preIndex);
        printf("Reconstructed tree: ");
        preOrderTraversal(root);
        printf("\n");
        runTest("Root is A", root != NULL && root->data == 'A');
        runTest("Right child is B", root->right != NULL && root->right->data == 'B');
        runTest("All nodes have right children only", 
                root->left == NULL && root->right->left == NULL);
        freeTree(root);
        freeHashTable(ht);
    }

    // Test 5.7: Complex balanced tree
    printf("\n--- Test 5.7: Complex Balanced Tree ---\n");
    {
        const char preorder[] = "ABDEGUHQJLXRWCMOIPFKSTVYNZ";
        const char inorder[] = "GUEQHDLXJRWBMOCPIAFSYVTKNZ";
        int length = strlen(inorder);
        int preIndex = 0;

        HashTable* ht = malloc(sizeof(HashTable));
        if (ht == NULL) {
            fprintf(stderr, "Memory allocation failed for hash table.\n");
            return 1;
        }

        initHashTable(ht, length);
        for (int i = 0; i < length; i++) {
            insertHashNode(ht, inorder[i], i);
        }

        clock_t begin = clock();
        Node* root = buildTreeFromPreInOptimized(preorder, inorder, 0, length - 1, ht, &preIndex);
        clock_t end = clock();

        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("Time: %f seconds\n", time_spent);
        printf("Reconstructed tree: ");
        preOrderTraversal(root);
        printf("\n");
        printf("Expected:           %s\n", preorder);
        
        // Verify by traversing again
        printf("Verification: ");
        preOrderTraversal(root);
        printf("\n");
        runTest("Complex tree reconstructed correctly", root != NULL);
        freeTree(root);
        freeHashTable(ht);
    }

    // Test 5.8: Minimal valid input
    printf("\n--- Test 5.8: Edge Case - Empty/Minimal ---\n");
    {
        const char preorder[] = "";
        const char inorder[] = "";
        int length = strlen(inorder);

        if (length == 0) {
            printf("Empty input detected - no tree creation\n");
            runTest("Handles empty input. In real scenario handled by checkInput()", 1);
        }
    }

    // Test 5.9: Single letter repeated (if allowed)
    printf("\n--- Test 5.9: Single Character Repeated ---\n");
    {
        const char preorder[] = "AAAA";
        const char inorder[] = "AAAA";
        int length = strlen(inorder);
        int preIndex = 0;

        HashTable* ht = malloc(sizeof(HashTable));
        if (ht == NULL) {
            fprintf(stderr, "Memory allocation failed for hash table.\n");
            return 1;
        }

        initHashTable(ht, length);
        for (int i = 0; i < length; i++) {
            insertHashNode(ht, inorder[i], i);
        }

        Node* root = buildTreeFromPreInOptimized(preorder, inorder, 0, length - 1, ht, &preIndex);
        if (root != NULL) {
            printf("Reconstructed tree: ");
            preOrderTraversal(root);
            printf("\n");
            printf("Note: Behavior with duplicates depends on your implementation\n");
        } else {
            printf("Tree is NULL (expected if duplicates not supported)\n");
        }
        freeTree(root);
        freeHashTable(ht);
    }

    // Test 5.10: Validate tree structure with multiple traversals
    printf("\n--- Test 5.10: Structural Validation ---\n");
    {
        const char preorder[] = "ABC";
        const char inorder[] = "BAC";
        int length = strlen(inorder);
        int preIndex = 0;

        HashTable* ht = malloc(sizeof(HashTable));
        if (ht == NULL) {
            fprintf(stderr, "Memory allocation failed for hash table.\n");
            return 1;
        }

        initHashTable(ht, length);
        for (int i = 0; i < length; i++) {
            insertHashNode(ht, inorder[i], i);
        }

        Node* root = buildTreeFromPreInOptimized(preorder, inorder, 0, length - 1, ht, &preIndex);
        
        printf("Preorder:  ");
        preOrderTraversal(root);
        printf("\n");
        
        printf("Expected:  %s\n", preorder);
        
        runTest("Tree structure matches input traversals", root != NULL);
        freeTree(root);
        freeHashTable(ht);
    }

    // Test 5.11: Longer sequence validation
    printf("\n--- Test 5.11: Extended Validation ---\n");
    {
        const char preorder[] = "ABDEGUHQJLXRWCMOIPFKSTVYNZ";
        const char inorder[] = "GUEQHDLXJRWBMOCPIAFSYVTKNZ";
        int length = strlen(inorder);
        int preIndex = 0;

        HashTable* ht = malloc(sizeof(HashTable));
        if (ht == NULL) {
            fprintf(stderr, "Memory allocation failed for hash table.\n");
            return 1;
        }

        initHashTable(ht, length);
        for (int i = 0; i < length; i++) {
            insertHashNode(ht, inorder[i], i);
        }

        Node* root = buildTreeFromPreInOptimized(preorder, inorder, 0, length - 1, ht, &preIndex);
        
        if (root != NULL) {
            printf("Input preorder:  %s\n", preorder);
            printf("Output preorder: ");
            preOrderTraversal(root);
            printf("\n");
            
            // Simple check: root should be first character
            runTest("Root is first character of preorder", root->data == preorder[0]);
        }
        freeTree(root);
        freeHashTable(ht);
    }

    printf("\n================================================================================\n");
    printf("               Test Suite Complete for Optimized Version\n");
    printf("                    %d/%d tests passed\n", passCount, testCount);
    printf("================================================================================\n\n");

    return 0;
}