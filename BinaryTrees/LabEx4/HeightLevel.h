#ifndef HEIGHT_LEVEL_H
#define HEIGHT_LEVEL_H
#include <stdio.h>
#include <stdlib.h>
#include "../Common/tree.h"
#include "../Common/queue.h"

void printLevels(const Node* root);
int getHeight(const Node* root);
void printHeight(const Node* root);

#endif