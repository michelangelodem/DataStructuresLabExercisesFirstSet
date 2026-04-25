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