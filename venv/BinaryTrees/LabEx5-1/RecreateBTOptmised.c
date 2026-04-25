#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
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

int main(void) {
    const char preorder[] = "ABDEGUHQJLXRWCMOIPFKSTVYNZ";
    const char inorder[] = "GUEQHDLXJRWBMOCPIAFSYVTKNZ";
    const char postorder[] = "UGQHEXLWRJDOMPICBYVTSZNKFA";

    int length = strlen(inorder);
    int preIndex = 0;
    int postIndex = length - 1;

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
    Node* root1 = buildTreeFromPostInOptimized(postorder, inorder, 0, length - 1, ht, &postIndex);
    Node* root2 = buildTreeFromPreInOptimized(preorder, inorder, 0, length - 1, ht, &preIndex);
    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time taken to build trees (optimized): %f seconds\n", time_spent);

    printf("Preorder Traversal of the reconstructed tree from postorder (optimized): ");
    preOrderTraversal(root1);
    printf("\n");

    printf("Preorder Traversal of the reconstructed tree from preorder (optimized): ");
    preOrderTraversal(root2);
    printf("\n");

    freeTree(root1);
    freeTree(root2);
    freeHashTable(ht);
    free(ht);
    return 0;
}