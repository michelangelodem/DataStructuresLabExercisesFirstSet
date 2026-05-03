#include "RecreateComparison.h"

// ==================== Traversal Functions ====================

void preOrderTraversal(const Node* root) {
    if (root == NULL) {
        return;
    }

    printf("%d ", root->data);
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

void inOrderTraversal(const Node* root) {
    if (root == NULL) {
        return;
    }

    inOrderTraversal(root->left);
    printf("%d ", root->data);
    inOrderTraversal(root->right);
}

void generateInOrderArray(const Node* root, int* array, int* index) {
    if (root == NULL) {
        return;
    }

    generateInOrderArray(root->left, array, index);
    array[(*index)++] = root->data;
    generateInOrderArray(root->right, array, index);
}

void generatePreOrderArray(const Node* root, int* array, int* index) {
    if (root == NULL) {
        return;
    }

    array[(*index)++] = root->data;
    generatePreOrderArray(root->left, array, index);
    generatePreOrderArray(root->right, array, index);
}

int countNodes(const Node* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);

}

// ==================== Integer Hash Table Functions ====================

void initIntHashTable(IntHashTable* ht, int size) {
    if (size <= 0) {
        size = TABLE_SIZE;
    }

    ht->numOfElements = 0;
    ht->size = size < TABLE_SIZE ? size : TABLE_SIZE;
    ht->table = (IntHashNode**)malloc(sizeof(IntHashNode*) * ht->size);

    if (ht->table == NULL) {
        ht->size = 0;
        ht->nodes_pool = NULL;
        return;
    }

    for (int i = 0; i < ht->size; i++) {
        ht->table[i] = NULL;
    }

    ht->pool_cap = TABLE_SIZE;
    ht->pool_idx = 0;
    ht->nodes_pool = (IntHashNode*)malloc(sizeof(IntHashNode) * (size_t)ht->pool_cap);
}

unsigned int intHashFunction(const IntHashTable* ht, int key) {
    return (unsigned int)key % ht->size;
}

void insertIntHashNode(IntHashTable* ht, int key, int value) {
    if (ht == NULL || ht->table == NULL || ht->size == 0) {
        return;
    }
    unsigned int index = intHashFunction(ht, key);
    IntHashNode* newHNode;

    if (ht->nodes_pool != NULL && ht->pool_idx < ht->pool_cap) {
        newHNode = &ht->nodes_pool[ht->pool_idx++];
    } else {
        newHNode = (IntHashNode*)malloc(sizeof(IntHashNode));
        if (newHNode == NULL) return;
    }
    newHNode->key = key;
    newHNode->value = value;
    newHNode->next = NULL;
    newHNode->next = ht->table[index];
    ht->table[index] = newHNode;
    ht->numOfElements++;
}

int getIntHashNodeValue(IntHashTable* ht, int key) {
    if (ht == NULL || ht->table == NULL || ht->size == 0) {
        return -1;
    }
    unsigned int index = intHashFunction(ht, key);
    IntHashNode* current = ht->table[index];
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return -1;
}

void freeIntHashTable(IntHashTable* ht) {
    if (ht == NULL || ht->table == NULL) {
        return;
    }

    for (int i = 0; i < ht->size; i++) {
        IntHashNode* current = ht->table[i];
        while (current != NULL) {
            IntHashNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(ht->table);
    if (ht->nodes_pool != NULL) {
        free(ht->nodes_pool);
    }
    ht->table = NULL;
    ht->pool_cap = 0;
    ht->pool_idx = 0;
    ht->size = 0;
    ht->numOfElements = 0;
}

// ==================== Unoptimized Version ====================

static int findIndex(const int inorder[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (inorder[i] == value) {
            return i;
        }
    }
    return -1;
}

Node* buildTreeFromPreInUnoptimized(const int preorder[], const int inorder[], int inStart, int inEnd, int* preIndex) {
    if (inStart > inEnd || *preIndex < 0) {
        return NULL;
    }

    int current = preorder[(*preIndex)++];
    Node* node = createNode(current);
    if (node == NULL) {
        return NULL;
    }

    if (inStart == inEnd) {
        return node;
    }

    int inIndex = findIndex(inorder, inStart, inEnd, current);
    if (inIndex == -1) {
        return node;
    }

    node->left = buildTreeFromPreInUnoptimized(preorder, inorder, inStart, inIndex - 1, preIndex);
    node->right = buildTreeFromPreInUnoptimized(preorder, inorder, inIndex + 1, inEnd, preIndex);
    return node;
}

// ==================== Optimized Version with Hash Table ====================

Node* buildTreeFromPreInOptimized(const int preorder[], const int inorder[], int inStart, int inEnd, IntHashTable* ht, int* preIndex) {
    if (inStart > inEnd || *preIndex < 0) {
        return NULL;
    }

    int current = preorder[(*preIndex)++];
    Node* node = createNode(current);
    if (node == NULL) {
        return NULL;
    }

    if (inStart == inEnd) {
        return node;
    }

    int inIndex = getIntHashNodeValue(ht, current);
    if (inIndex < inStart || inIndex > inEnd) {
        return node;
    }

    node->left = buildTreeFromPreInOptimized(preorder, inorder, inStart, inIndex - 1, ht, preIndex);
    node->right = buildTreeFromPreInOptimized(preorder, inorder, inIndex + 1, inEnd, ht, preIndex);
    return node;
}