#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>
#include "../Common/tree.h"

Node* binaryTreeSearch(Node* root, int key);
Node* insertNode(Node* root, int key);
Node* findMin(Node* node);
Node* deleteNode(Node* root, int key);
#endif