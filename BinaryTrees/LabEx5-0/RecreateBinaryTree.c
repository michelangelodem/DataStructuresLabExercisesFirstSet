#include "RecreateBinaryTree.h"

static int findIndex(const char inorder[], int start, int end, char value) {
    for (int i = start; i <= end; i++) {
        if (inorder[i] == value) {
            return i;
        }
    }
    return -1;
}

Node* buildTreeFromPreIn(const char preorder[], const char inorder[], int inStart, int inEnd, int* preIndex) {
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

    int inIndex = findIndex(inorder, inStart, inEnd, current);
    if (inIndex == -1) {
        return node;
    }

    node->left = buildTreeFromPreIn(preorder, inorder, inStart, inIndex - 1, preIndex);
    node->right = buildTreeFromPreIn(preorder, inorder, inIndex + 1, inEnd, preIndex);
    return node;
}

Node* buildTreeFromPostIn(const char postorder[], const char inorder[], int inStart, int inEnd, int* postIndex) {
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

    int inIndex = findIndex(inorder, inStart, inEnd, current);
    if (inIndex == -1) {
        return node;
    }

    node->right = buildTreeFromPostIn(postorder, inorder, inIndex + 1, inEnd, postIndex);
    node->left = buildTreeFromPostIn(postorder, inorder, inStart, inIndex - 1, postIndex);
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