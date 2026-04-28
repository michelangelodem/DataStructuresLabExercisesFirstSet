#ifndef RECREATE_BINARY_TREE_H
#define RECREATE_BINARY_TREE_H
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../Common/tree.h"

static int findIndex(const char inorder[], int start, int end, char value);
Node* buildTreeFromPreIn(const char preorder[], const char inorder[], int inStart, int inEnd, int* preIndex);
Node* buildTreeFromPostIn(const char postorder[], const char inorder[], int inStart, int inEnd, int* postIndex);

// Utility functions for testing and validation

void preOrderTraversal(const Node* root);
bool checkInput(const char* preorder, const char* inorder, const char* postorder);

#endif 