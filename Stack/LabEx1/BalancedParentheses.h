#ifndef BALANCED_PARANTHESES_H
#define BALANCED_PARANTHESES_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int top;
    char data[MAX_SIZE];
} Stack;

void push(Stack *stack, char value);
char pop(Stack *stack);
bool isMatchingPair(char open, char close);
int checkExpression(const char expression[]);
#endif