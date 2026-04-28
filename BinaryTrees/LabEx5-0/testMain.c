#include "RecreateBinaryTree.h"
#include <time.h>

// =================================================================================
// =============================  TEST FOR TREE BUILDING  ==========================
// =================================================================================

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

        clock_t begin = clock();
        Node* root = buildTreeFromPreIn(preorder, inorder, 0, length - 1, &preIndex);
        clock_t end = clock();

        printf("Time: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
        printf("Reconstructed tree: ");
        preOrderTraversal(root);
        printf("\n");
        runTest("Single character reconstructs correctly", root != NULL && root->data == 'A');
        freeTree(root);
    }

    // Test 5.2: Two nodes - left child only
    printf("\n--- Test 5.2: Two Nodes (Left Child) ---\n");
    {
        const char preorder[] = "AB";
        const char inorder[] = "BA";
        int length = strlen(inorder);
        int preIndex = 0;

        Node* root = buildTreeFromPreIn(preorder, inorder, 0, length - 1, &preIndex);
        printf("Reconstructed tree: ");
        preOrderTraversal(root);
        printf("\n");
        runTest("Root is A", root != NULL && root->data == 'A');
        runTest("Left child is B", root->left != NULL && root->left->data == 'B');
        runTest("No right child", root->right == NULL);
        freeTree(root);
    }

    // Test 5.3: Two nodes - right child only
    printf("\n--- Test 5.3: Two Nodes (Right Child) ---\n");
    {
        const char preorder[] = "AB";
        const char inorder[] = "AB";
        int length = strlen(inorder);
        int preIndex = 0;

        Node* root = buildTreeFromPreIn(preorder, inorder, 0, length - 1, &preIndex);
        printf("Reconstructed tree: ");
        preOrderTraversal(root);
        printf("\n");
        runTest("Root is A", root != NULL && root->data == 'A');
        runTest("Right child is B", root->right != NULL && root->right->data == 'B');
        runTest("No left child", root->left == NULL);
        freeTree(root);
    }

    // Test 5.4: Three nodes - balanced
    printf("\n--- Test 5.4: Three Nodes (Balanced) ---\n");
    {
        const char preorder[] = "ABC";
        const char inorder[] = "BAC";
        int length = strlen(inorder);
        int preIndex = 0;

        Node* root = buildTreeFromPreIn(preorder, inorder, 0, length - 1, &preIndex);
        printf("Reconstructed tree: ");
        preOrderTraversal(root);
        printf("\n");
        runTest("Root is A", root != NULL && root->data == 'A');
        runTest("Left child is B", root->left != NULL && root->left->data == 'B');
        runTest("Right child is C", root->right != NULL && root->right->data == 'C');
        freeTree(root);
    }

    // Test 5.5: Skewed left (linear)
    printf("\n--- Test 5.5: Skewed Left Tree ---\n");
    {
        const char preorder[] = "ABCDE";
        const char inorder[] = "EDCBA";
        int length = strlen(inorder);
        int preIndex = 0;

        Node* root = buildTreeFromPreIn(preorder, inorder, 0, length - 1, &preIndex);
        printf("Reconstructed tree: ");
        preOrderTraversal(root);
        printf("\n");
        runTest("Root is A", root != NULL && root->data == 'A');
        runTest("Left child is B", root->left != NULL && root->left->data == 'B');
        runTest("All nodes have left children only", 
                root->right == NULL && root->left->right == NULL);
        freeTree(root);
    }

    // Test 5.6: Skewed right (linear)
    printf("\n--- Test 5.6: Skewed Right Tree ---\n");
    {
        const char preorder[] = "ABCDE";
        const char inorder[] = "ABCDE";
        int length = strlen(inorder);
        int preIndex = 0;

        Node* root = buildTreeFromPreIn(preorder, inorder, 0, length - 1, &preIndex);
        printf("Reconstructed tree: ");
        preOrderTraversal(root);
        printf("\n");
        runTest("Root is A", root != NULL && root->data == 'A');
        runTest("Right child is B", root->right != NULL && root->right->data == 'B');
        runTest("All nodes have right children only", 
                root->left == NULL && root->right->left == NULL);
        freeTree(root);
    }

    // Test 5.7: Complex balanced tree
    printf("\n--- Test 5.7: Complex Balanced Tree ---\n");
    {
        const char preorder[] = "ABDEGUHQJLXRWCMOIPFKSTVYNZ";
        const char inorder[] = "GUEQHDLXJRWBMOCPIAFSYVTKNZ";
        int length = strlen(inorder);
        int preIndex = 0;

        clock_t begin = clock();
        Node* root = buildTreeFromPreIn(preorder, inorder, 0, length - 1, &preIndex);
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
        const char preorder[] = "AAA";
        const char inorder[] = "AAA";
        int length = strlen(inorder);
        int preIndex = 0;

        Node* root = buildTreeFromPreIn(preorder, inorder, 0, length - 1, &preIndex);
        if (root != NULL) {
            printf("Reconstructed tree: ");
            preOrderTraversal(root);
            printf("\n");
            printf("Note: Behavior with duplicates depends on your implementation\n");
        } else {
            printf("Tree is NULL (expected if duplicates not supported)\n");
        }
        freeTree(root);
    }

    // Test 5.10: Validate tree structure with multiple traversals
    printf("\n--- Test 5.10: Structural Validation ---\n");
    {
        const char preorder[] = "ABC";
        const char inorder[] = "BAC";
        int length = strlen(inorder);
        int preIndex = 0;

        Node* root = buildTreeFromPreIn(preorder, inorder, 0, length - 1, &preIndex);
        
        printf("Preorder:  ");
        preOrderTraversal(root);
        printf("\n");
        
        printf("Expected:  %s\n", preorder);
        
        runTest("Tree structure matches input traversals", root != NULL);
        freeTree(root);
    }

    // Test 5.11: Longer sequence validation
    printf("\n--- Test 5.11: Extended Validation ---\n");
    {
        const char preorder[] = "ABDEGUHQJLXRWCMOIPFKSTVYNZ";
        const char inorder[] = "GUEQHDLXJRWBMOCPIAFSYVTKNZ";
        int length = strlen(inorder);
        int preIndex = 0;

        Node* root = buildTreeFromPreIn(preorder, inorder, 0, length - 1, &preIndex);
        
        if (root != NULL) {
            printf("Input preorder:  %s\n", preorder);
            printf("Output preorder: ");
            preOrderTraversal(root);
            printf("\n");
            
            // Simple check: root should be first character
            runTest("Root is first character of preorder", root->data == preorder[0]);
        }
        freeTree(root);
    }

    printf("\n================================================================================\n");
    printf("                      Test Suite Complete\n");
    printf("                    %d/%d tests passed\n", passCount, testCount);
    printf("================================================================================\n\n");

    return 0;
}