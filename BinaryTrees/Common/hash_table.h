#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct HashNode {
    char key;
    unsigned int value;
    struct HashNode* next;
} HashNode;

void setHashNode(HashNode* n, char key, unsigned int value);

typedef struct HashTable {
    int numOfElements;
    int size;
    HashNode** table;
    // pre-allocated κομματι μνημης για τα nodes του hash table, 
    // ωστε να μειωσουμε τα malloc calls και να αποφευχθουν cache crashes.
    HashNode* nodes_pool; 
    int pool_idx;
    int pool_cap;
} HashTable;

void initHashTable(HashTable* ht, int size);
unsigned int hashFunction(const HashTable* ht, char key);
void insertHashNode(HashTable* ht, char key, unsigned int value);
int getHashNodeValueInRange(HashTable* ht, char key, int start, int end);
void freeHashTable(HashTable* ht);

#endif