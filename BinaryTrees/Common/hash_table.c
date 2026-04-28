#include "hash_table.h"

/*
 Hash table υλοποίηση για αντιστοίχηση χαρακτήρων σε ακέραιες τιμές. 
 Χρησημοποιείται απο την LabEx5-1 για βελτιστοποίηση της αναζήτησης των δεικτών των χαρακτήρων στο inorder traversal.
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
    return (unsigned char)key % ht->size;
}

void insertHashNode(HashTable* ht, char key, unsigned int value) {
    if (ht == NULL || ht->table == NULL || ht->size == 0) {
        return;
    }

    unsigned int index = hashFunction(ht, key);
    HashNode* newHNode = (HashNode*)malloc(sizeof(HashNode));
    if (newHNode == NULL) {
        return;
    }

    setHashNode(newHNode, key, value);
    newHNode->next = ht->table[index];
    ht->table[index] = newHNode;
    ht->numOfElements++;
}

void deleteHashNode(HashTable* ht, char key) {
    if (ht == NULL || ht->table == NULL || ht->size == 0) {
        return;
    }

    unsigned int index = hashFunction(ht, key);
    HashNode* current = ht->table[index];
    HashNode* prev = NULL;

    while (current != NULL) {
        if (current->key == key) {
            if (prev == NULL) {
                ht->table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            ht->numOfElements--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

int getHashNodeValue(HashTable* ht, char key) {
    if (ht == NULL || ht->table == NULL || ht->size == 0) {
        return -1;
    }

    unsigned int index = hashFunction(ht, key);
    HashNode* current = ht->table[index];
    while (current != NULL) {
        if (current->key == key) {
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
    free(ht->table);
    ht->size = 0;
    ht->numOfElements = 0;
}