#ifndef RECREATE_COMPARISON_H
#define RECREATE_COMPARISON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../Common/tree.h"

#define TABLE_SIZE 1048576  // Size of the hash table for optimized version (can be adjusted based on expected tree size)

typedef struct IntHashNode {
    int key;
    int value;
    struct IntHashNode* next;
} IntHashNode;


// Για να μην δημιουργουνται cache crasses 
// λογω ων συνεχωμενων malloc που εκτελεουνται 
// για το hash table, θα χρησημοποιησουμε μια σταθερη 
// μεγαλη συνεχομενη περιοχη μνημης για το hash table.
typedef struct IntHashTable {
    int numOfElements;
    int size;
    IntHashNode** table;

    IntHashNode* nodes_pool; 
    int pool_idx;
    int pool_cap;
} IntHashTable;

// Utility traversal functions
void preOrderTraversal(const Node* root);
void inOrderTraversal(const Node* root);
void generateInOrderArray(const Node* root, int* array, int* index);
void generatePreOrderArray(const Node* root, int* array, int* index);
int countNodes(const Node* root);

// Integer hash table functions (different from character-based hash table)
void initIntHashTable(IntHashTable* ht, int size);
void insertIntHashNode(IntHashTable* ht, int key, int value);
int getIntHashNodeValue(IntHashTable* ht, int key);
void freeIntHashTable(IntHashTable* ht);

// Unoptimized version
static int findIndex(const int inorder[], int start, int end, int value);
Node* buildTreeFromPreInUnoptimized(const int preorder[], const int inorder[], int inStart, int inEnd, int* preIndex);

// Optimized version with hash table
Node* buildTreeFromPreInOptimized(const int preorder[], const int inorder[], int inStart, int inEnd, IntHashTable* ht, int* preIndex);
#endif
