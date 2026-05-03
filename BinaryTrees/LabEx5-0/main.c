#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    Node* root1 = buildTreeFromPreIn(preorder, inorder, 0, length - 1, &preIndex);
    Node* root2 = buildTreeFromPostIn(postorder, inorder, 0, length - 1, &postIndex);

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