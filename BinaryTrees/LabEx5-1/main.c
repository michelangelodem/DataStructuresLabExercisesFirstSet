#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RecreateBTOptimised.h"

int main(void) {
    const char preorder[] = "ABDEGUHQJLXRWCMOIPFKSTVYNZ";
    const char inorder[] = "GUEQHDLXJRWBMOCPIAFSYVTKNZ";
    const char postorder[] = "UGQHEXLWRJDOMPICBYVTSZNKFA";

    if (!checkInput(preorder, inorder, postorder)) {
        return 1;
    }

    int length = strlen(inorder);
    int preIndex = 0;
    int postIndex = length - 1;

    HashTable* ht = malloc(sizeof(HashTable));
    if (ht == NULL) {
        fprintf(stderr, "Memory allocation failed for hash table.\n");
        return 1;
    }

    initHashTable(ht, length);
    for (int i = 0; i < length; i++) {
        insertHashNode(ht, inorder[i], i);
    }

    Node* root1 = buildTreeFromPostInOptimized(postorder, inorder, 0, length - 1, ht, &postIndex);
    Node* root2 = buildTreeFromPreInOptimized(preorder, inorder, 0, length - 1, ht, &preIndex);

    printf("Preorder Traversal of the reconstructed tree from postorder (optimized): ");
    preOrderTraversal(root1);
    printf("\n");

    printf("Preorder Traversal of the reconstructed tree from preorder (optimized): ");
    preOrderTraversal(root2);
    printf("\n");

    freeTree(root1);
    freeTree(root2);
    freeHashTable(ht);
    free(ht);
    return 0;
}