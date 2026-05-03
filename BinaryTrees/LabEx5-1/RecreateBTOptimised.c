#include "RecreateBTOptimised.h"

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

    int inIndex = getHashNodeValueInRange(ht, current, inStart, inEnd);
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

    int inIndex = getHashNodeValueInRange(ht, current, inStart, inEnd);
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