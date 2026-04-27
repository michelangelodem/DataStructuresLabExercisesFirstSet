#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 1000

typedef struct
{
    int data[MAX_SIZE];
    int S[MAX_SIZE];
    int AUX[MAX_SIZE];
    int top;
}SparseArray;

SparseArray* initialize() {
    SparseArray *sparseArray = (SparseArray*)malloc(sizeof(SparseArray));
    if (sparseArray) {
        sparseArray->top = 0;
    }
    return sparseArray;
}

bool isInitialized(SparseArray *sparseArray, int i) {
    return ((0 <= sparseArray->AUX[i] 
        && sparseArray->AUX[i] < sparseArray->top) 
        && (sparseArray->S[sparseArray->AUX[i]] == i));
}

void write(SparseArray *sparseArray, int i, int val) {
    if (isInitialized(sparseArray, i)) {
        sparseArray->data[i] = val;
    }
    if (sparseArray->top == MAX_SIZE) {
        printf("Sparse array is full.\n");
    }
    if (i < 0 || i >= MAX_SIZE) {
        printf("Index out of bounds.\n");
    }
    else {
        sparseArray->S[sparseArray->top] = i;
        sparseArray->AUX[i] = sparseArray->top;
        sparseArray->top++;
        sparseArray->data[i] = val;
    }
}

int read(SparseArray *sparseArray, int i) {
    if (isInitialized(sparseArray, i)) {
        return sparseArray->data[i];
    }
    else {
        return 0;
    }
}

int main() {
    SparseArray *sparseArray = initialize();

    write(sparseArray, 5, 10);
    write(sparseArray, 100, 20);
    write(sparseArray, 999, 30);

    printf("%d\n", read(sparseArray, 5)); // Output: 10
    printf("%d\n", read(sparseArray, 100)); // Output: 20
    printf("%d\n", read(sparseArray, 999)); // Output: 30
    printf("%d\n", read(sparseArray, 50)); // Output: 0

    free(sparseArray);
    return 0;
}