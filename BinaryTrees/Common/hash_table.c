#include "hash_table.h"

/*
 Hash table υλοποίηση για αντιστοίχηση χαρακτήρων σε ακέραιες τιμές. 
 Χρησιμοποιείται από την LabEx5-1 για βελτιστοποίηση της αναζήτησης των δεικτών των χαρακτήρων στο inorder traversal.
 Έχοντας ως κλειδιά τους χαρακτήρες του inorder traversal και ως τιμές τους αντίστοιχους δείκτες τους.
 Έτσι μπορούμε να βρούμε γρήγορα τη θέση ενός χαρακτήρα στο inorder traversal, 
 μειώνοντας τον χρόνο κατασκευής του δέντρου από O(n^2) σε O(n).
*/

void setHashNode(HashNode* n, char key, unsigned int value) {
    n->key = key;
    n->value = value;
    n->next = NULL;
} 

void initHashTable(HashTable* ht, int size) {
    if (size <= 0) {
        size = TABLE_SIZE;
    }
    ht->numOfElements = 0;
    ht->size = size < TABLE_SIZE ? size : TABLE_SIZE;
    ht->table = (HashNode**)malloc(sizeof(HashNode*) * ht->size);
    if (ht->table == NULL) {
        ht->size = 0;
        return;
    }
    for (int i = 0; i < ht->size; i++) {
        ht->table[i] = NULL;
    }
}

unsigned int hashFunction(const HashTable* ht, char key) {
    return ((unsigned char)key) % ht->size;
}

void insertHashNode(HashTable* ht, char key, unsigned int value) {
    if (ht == NULL || ht->table == NULL || ht->size == 0) {
        return;
    }
    unsigned int index = hashFunction(ht, key);
    HashNode* newHNode;

    if (ht->nodes_pool != NULL && ht->pool_idx < ht->pool_cap) {
        newHNode = &ht->nodes_pool[ht->pool_idx++];
    } else {
        newHNode = (HashNode*)malloc(sizeof(HashNode));
        if (newHNode == NULL) return;
    }
    newHNode->key = key;
    newHNode->value = value;
    newHNode->next = NULL;
    newHNode->next = ht->table[index];
    ht->table[index] = newHNode;
    ht->numOfElements++;
}

int getHashNodeValueInRange(HashTable* ht, char key, int start, int end) {
    if (ht == NULL || ht->table == NULL || ht->size == 0) {
        return -1;
    }

    unsigned int index = hashFunction(ht, key);
    HashNode* current = ht->table[index];
    while (current != NULL) {
        if (current->key == key && current->value >= (unsigned int)start && current->value <= (unsigned int)end) {
            return current->value;
        }
        current = current->next;
    }
    return -1;
}

void freeHashTable(HashTable* ht) {
    if (ht == NULL || ht->table == NULL) {
        return;
    }

    for (int i = 0; i < ht->size; i++) {
        HashNode* current = ht->table[i];
        while (current != NULL) {
            HashNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    ht->table = NULL;
    ht->pool_cap = 0;
    ht->pool_idx = 0;
    ht->size = 0;
    ht->numOfElements = 0;
}