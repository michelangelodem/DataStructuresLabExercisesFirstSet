#include "HeightLevel.h"

// =================================================================================
// =============================  TEST TREE HEIGHT AND LEVEL  ======================
// =================================================================================

int testCount = 0;
int passCount = 0;

// Δε΄ίτε την LabEx2/testMain.c

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
    printf("=== Test 4.1: NULL Tree ===\n");
    getHeight(NULL);  // Should return 0 without crashing
    runTest("NULL tree height is 0", getHeight(NULL) == 0);
    printf("Levels in NULL tree:\n");
    printLevels(NULL);  // Should not print anything and not crash
    printf("\n");

    printf("=== Test 4.2: Single Node Tree ===\n");
    Node* root = createNode(50);
    runTest("Single node height is 1", getHeight(root) == 1);
    printf("Levels in single node tree:\n");
    printLevels(root);
    printf("\n");
    freeTree(root);

    printf("=== Test 4.3: Two Nodes (Left Child) ===\n");
    root = createNode(50);
    root->left = createNode(30);
    runTest("Tree height is 2", getHeight(root) == 2);
    printf("Levels:\n");
    printLevels(root);
    printf("Height: %d\n", getHeight(root));
    printf("\n");
    freeTree(root);

    printf("=== Test 4.4: Two Nodes (Right Child) ===\n");
    root = createNode(50);
    root->right = createNode(70);
    runTest("Tree height is 2", getHeight(root) == 2);
    printf("Levels:\n");
    printLevels(root);
    printf("Height: %d\n", getHeight(root));
    printf("\n");
    freeTree(root);

    printf("=== Test 4.5: Balanced Tree (Height 3) ===\n");
    root = createNode(50);
    root->left = createNode(30);
    root->right = createNode(70);
    root->left->left = createNode(20);
    root->left->right = createNode(40);
    root->right->left = createNode(60);
    root->right->right = createNode(80);
    runTest("Balanced tree height is 3", getHeight(root) == 3);
    printf("Levels:\n");
    printLevels(root);
    printf("Height: %d\n", getHeight(root));
    printf("\n");
    freeTree(root);

    printf("=== Test 4.6: Skewed Left Tree ===\n");
    root = createNode(50);
    root->left = createNode(40);
    root->left->left = createNode(30);
    root->left->left->left = createNode(20);
    root->left->left->left->left = createNode(10);
    runTest("Skewed left tree height is 5", getHeight(root) == 5);
    printf("Levels:\n");
    printLevels(root);
    printf("Height: %d\n", getHeight(root));
    printf("\n");
    freeTree(root);

    printf("=== Test 4.7: Skewed Right Tree ===\n");
    root = createNode(10);
    root->right = createNode(20);
    root->right->right = createNode(30);
    root->right->right->right = createNode(40);
    root->right->right->right->right = createNode(50);
    runTest("Skewed right tree height is 5", getHeight(root) == 5);
    printf("Levels:\n");
    printLevels(root);
    printf("Height: %d\n", getHeight(root));
    printf("\n");
    freeTree(root);

    printf("=== Test 4.8: Complex Tree ===\n");
    root = createNode(100);
    root->left = createNode(50);
    root->right = createNode(150);
    root->left->left = createNode(25);
    root->left->right = createNode(75);
    root->right->right = createNode(200);
    root->right->right->right = createNode(250);
    runTest("Complex tree height is 4", getHeight(root) == 4);
    printf("Levels:\n");
    printLevels(root);
    printf("Height: %d\n", getHeight(root));
    printf("\n");
    freeTree(root);

    printf("================================================================================\n");
    printf("Test Results: %d/%d tests passed\n", passCount, testCount);
    printf("================================================================================\n");

    return (passCount == testCount) ? 0 : 1;
}