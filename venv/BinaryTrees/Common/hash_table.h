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
} HashTable;

void initHashTable(HashTable* ht, int size);
unsigned int hashFunction(const HashTable* ht, char key);
void insertHashNode(HashTable* ht, char key, unsigned int value);
void deleteHashNode(HashTable* ht, char key);
int getHashNodeValue(HashTable* ht, char key);
void freeHashTable(HashTable* ht);

#endif