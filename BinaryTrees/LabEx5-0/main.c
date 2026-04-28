#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "RecreateBinaryTree.h" 

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

    clock_t begin = clock();
    Node* root1 = buildTreeFromPreIn(preorder, inorder, 0, length - 1, &preIndex);
    Node* root2 = buildTreeFromPostIn(postorder, inorder, 0, length - 1, &postIndex);
    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time taken to build trees (unoptimized): %f seconds\n", time_spent);

    printf("Preorder Traversal of the reconstructed tree: ");
    preOrderTraversal(root1);
    printf("\n");

    printf("Preorder Traversal of the reconstructed tree from postorder: ");
    preOrderTraversal(root2);
    printf("\n");

    freeTree(root1);
    freeTree(root2);
    return 0;
}