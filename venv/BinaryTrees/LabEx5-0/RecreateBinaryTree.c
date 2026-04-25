#include <time.h>
#include <string.h>
#include <stdio.h>
#include "../Common/tree.h"

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

int main(void) {
    const char preorder[] = "ABDEGUHQJLXRWCMOIPFKSTVYNZ";
    const char inorder[] = "GUEQHDLXJRWBMOCPIAFSYVTKNZ";
    const char postorder[] = "UGQHEXLWRJDOMPICBYVTSZNKFA";

    int length = strlen(inorder);
    int preIndex = 0;
    int postIndex = length - 1;

    clock_t begin = clock();
    Node* root1 = buildTreeFromPreIn(preorder, inorder, 0, length - 1, &preIndex);
    Node* root2 = buildTreeFromPostIn(postorder, inorder, 0, length - 1, &postIndex);
    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time taken to build trees (unoptimized): %f seconds\n", time_spent);

    printf("Preorder Traversal of the reconstructed tree: ");
    preOrderTraversal(root1);
    printf("\n");

    printf("Preorder Traversal of the reconstructed tree from postorder: ");
    preOrderTraversal(root2);
    printf("\n");

    freeTree(root1);
    freeTree(root2);
    return 0;
}