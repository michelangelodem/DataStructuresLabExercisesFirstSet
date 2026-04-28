#ifndef ORDER_LEVEL_H
#define ORDER_LEVEL_H

#include <stdio.h>
#include <stdlib.h>
#include "../Common/tree.h"
#include "../Common/queue.h"

void printPreOrder(const Node* root);
void printPostOrder(const Node* root);
void printLevelOrder(const Node* root);

#endif 