#ifndef RECREATE_BT_OPTIMIZED_H
#define RECREATE_BT_OPTIMIZED_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Common/hash_table.h"
#include "../Common/tree.h"

Node* buildTreeFromPreInOptimized(const char preorder[], const char inorder[], int inStart, int inEnd, HashTable* ht, int* preIndex);
Node* buildTreeFromPostInOptimized(const char postorder[], const char inorder[], int inStart, int inEnd, HashTable* ht, int* postIndex);
void preOrderTraversal(const Node* root);
bool checkInput(const char* preorder, const char* inorder, const char* postorder);

#endif