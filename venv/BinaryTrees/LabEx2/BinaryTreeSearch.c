#include <stdio.h>
#include <stdlib.h>
#include "../Common/tree.h"

Node* binaryTreeSearch(Node* root, int key) {
    if (root == NULL) {
        return NULL;
    }
    if (root->data == key) {
        return root;
    }
    if (key < root->data) {
        return binaryTreeSearch(root->left, key);
    }
    return binaryTreeSearch(root->right, key);
}

Node* insertNode(Node* root, int key) {
    if (root == NULL) {
        return createNode(key);
    }

    if (key < root->data) {
        root->left = insertNode(root->left, key);
    } else {
        root->right = insertNode(root->right, key);
    }
    return root;
}

Node* findMin(Node* node) {
    while (node != NULL && node->left != NULL) {
        node = node->left;
    }
    return node;
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL) {
        return NULL;
    }

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = findMin(root->right);
        if (temp != NULL) {
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    return root;
}

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

// =================================================================================
// =============================  TEST FOR BINARY SEARCH TREE  ===================
// =================================================================================
// Uncomment τον παρακάτω κώδικα για να τρέξετε τα tests 
// και comment out τη main() παραπάνω.

// int testCount = 0;
// int passCount = 0;

// void runTest(const char* testName, int condition) {
//     testCount++;
//     if (condition) {
//         printf("Test %d PASS: %s\n", testCount, testName);
//         passCount++;
//     } else {
//         printf("Τest %d FAIL: %s\n", testCount, testName);
//     }
// }

// void inOrderTraversal(const Node* root) {
//     if (root == NULL) {
//         return;
//     }
//     inOrderTraversal(root->left);
//     printf("%d ", root->data);
//     inOrderTraversal(root->right);
// }

// int main(void) {

//     printf("--- Test 2.1: Search in NULL Tree ---\n");
//     Node* result = binaryTreeSearch(NULL, 42);
//     runTest("Search NULL tree returns NULL", result == NULL);

//     printf("\n--- Test 2.2: Single Node Tree ---\n");
//     Node* root = createNode(50);
//     result = binaryTreeSearch(root, 50);
//     runTest("Search finds single node", result != NULL && result->data == 50);
//     result = binaryTreeSearch(root, 25);
//     runTest("Search fails for missing key in single node", result == NULL);
//     freeTree(root);

//     printf("\n--- Test 2.3: Two Nodes (Left Child) ---\n");
//     root = createNode(50);
//     root = insertNode(root, 30);
//     result = binaryTreeSearch(root, 30);
//     runTest("Find left child", result != NULL && result->data == 30);
//     result = binaryTreeSearch(root, 70);
//     runTest("Missing right child returns NULL", result == NULL);
//     freeTree(root);

//     printf("\n--- Test 2.4: Two Nodes (Right Child) ---\n");
//     root = createNode(50);
//     root = insertNode(root, 70);
//     result = binaryTreeSearch(root, 70);
//     runTest("Find right child", result != NULL && result->data == 70);
//     result = binaryTreeSearch(root, 30);
//     runTest("Missing left child returns NULL", result == NULL);
//     freeTree(root);

//     printf("\n--- Test 2.5: Skewed Left Tree ---\n");
//     root = createNode(50);
//     root = insertNode(root, 40);
//     root = insertNode(root, 30);
//     root = insertNode(root, 20);
//     root = insertNode(root, 10);
//     printf("Tree structure (inorder): ");
//     inOrderTraversal(root);
//     printf("\n");
//     result = binaryTreeSearch(root, 10);
//     runTest("Find leftmost node", result != NULL && result->data == 10);
//     result = binaryTreeSearch(root, 30);
//     runTest("Find middle node", result != NULL && result->data == 30);
//     freeTree(root);

//     printf("\n--- Test 2.6: Skewed Right Tree ---\n");
//     root = createNode(10);
//     root = insertNode(root, 20);
//     root = insertNode(root, 30);
//     root = insertNode(root, 40);
//     root = insertNode(root, 50);
//     printf("Tree structure (inorder): ");
//     inOrderTraversal(root);
//     printf("\n");
//     result = binaryTreeSearch(root, 50);
//     runTest("Find rightmost node", result != NULL && result->data == 50);
//     result = binaryTreeSearch(root, 30);
//     runTest("Find middle node", result != NULL && result->data == 30);
//     freeTree(root);

//     printf("\n--- Test 2.7: Balanced Tree ---\n");
//     root = createNode(50);
//     root = insertNode(root, 30);
//     root = insertNode(root, 70);
//     root = insertNode(root, 20);
//     root = insertNode(root, 40);
//     root = insertNode(root, 60);
//     root = insertNode(root, 80);
//     printf("Tree structure (inorder): ");
//     inOrderTraversal(root);
//     printf("\n");
//     runTest("Find root in balanced tree", binaryTreeSearch(root, 50) != NULL);
//     runTest("Find left subtree root", binaryTreeSearch(root, 30) != NULL);
//     runTest("Find right subtree root", binaryTreeSearch(root, 70) != NULL);
//     runTest("Find leaf left", binaryTreeSearch(root, 20) != NULL);
//     runTest("Find leaf right", binaryTreeSearch(root, 80) != NULL);

//     printf("\n--- Test 2.8: Delete Leaf Node ---\n");
//     root = deleteNode(root, 20);
//     result = binaryTreeSearch(root, 20);
//     runTest("Leaf node deleted", result == NULL);
//     runTest("Other nodes still present", binaryTreeSearch(root, 50) != NULL);
//     freeTree(root);

//     printf("\n--- Test 2.9: Delete Node with One Child ---\n");
//     root = createNode(50);
//     root = insertNode(root, 30);
//     root = insertNode(root, 20);  // 30 has only left child
//     root = deleteNode(root, 30);
//     printf("After deleting 30: ");
//     inOrderTraversal(root);
//     printf("\n");
//     runTest("Node with one child deleted", binaryTreeSearch(root, 30) == NULL);
//     runTest("Child promoted", binaryTreeSearch(root, 20) != NULL);
//     freeTree(root);

//     printf("\n--- Test 2.10: Delete Node with Two Children ---\n");
//     root = createNode(50);
//     root = insertNode(root, 30);
//     root = insertNode(root, 70);
//     root = insertNode(root, 20);
//     root = insertNode(root, 40);
//     root = insertNode(root, 60);
//     root = insertNode(root, 80);
//     printf("Before deletion: ");
//     inOrderTraversal(root);
//     printf("\n");
//     root = deleteNode(root, 30);  // Delete with two children
//     printf("After deleting 30: ");
//     inOrderTraversal(root);
//     printf("\n");
//     runTest("Node with two children deleted", binaryTreeSearch(root, 30) == NULL);
//     runTest("Left subtree preserved", binaryTreeSearch(root, 20) != NULL);
//     runTest("Right subtree preserved", binaryTreeSearch(root, 40) != NULL);
//     freeTree(root);

//     printf("\n--- Test 2.11: Delete Root (No Children) ---\n");
//     root = createNode(42);
//     root = deleteNode(root, 42);
//     runTest("Root deleted, tree becomes NULL", root == NULL);

//     printf("\n--- Test 2.12: Delete Root (With Children) ---\n");
//     root = createNode(50);
//     root = insertNode(root, 30);
//     root = insertNode(root, 70);
//     root = insertNode(root, 20);
//     root = insertNode(root, 40);
//     root = deleteNode(root, 50);  // Delete root
//     printf("After deleting root: ");
//     inOrderTraversal(root);
//     printf("\n");
//     runTest("Root deleted", binaryTreeSearch(root, 50) == NULL);
//     runTest("Left subtree preserved", binaryTreeSearch(root, 30) != NULL);
//     runTest("Right subtree preserved", binaryTreeSearch(root, 70) != NULL);
//     freeTree(root);

//     printf("\n--- Test 2.13: Delete Non-Existent Key ---\n");
//     root = createNode(50);
//     root = insertNode(root, 30);
//     root = insertNode(root, 70);
//     Node* beforeDelete = root;
//     root = deleteNode(root, 999);  // Non-existent
//     printf("After attempting to delete 999: ");
//     inOrderTraversal(root);
//     printf("\n");
//     runTest("Tree unchanged", root == beforeDelete);
//     freeTree(root);

//     printf("\n--- Test 2.14: Complex Sequence ---\n");
//     root = NULL;
//     root = insertNode(root, 50);
//     root = insertNode(root, 30);
//     root = insertNode(root, 70);
//     root = insertNode(root, 20);
//     root = insertNode(root, 40);
//     root = insertNode(root, 60);
//     root = insertNode(root, 80);
//     printf("Initial tree: ");
//     inOrderTraversal(root);
//     printf("\n");
    
//     root = deleteNode(root, 20);
//     root = deleteNode(root, 80);
//     root = insertNode(root, 25);
//     printf("After delete 20,80 and insert 25: ");
//     inOrderTraversal(root);
//     printf("\n");
//     runTest("Complex sequence works", binaryTreeSearch(root, 25) != NULL && 
//                                        binaryTreeSearch(root, 20) == NULL);
//     freeTree(root);

//     return 0;
// }