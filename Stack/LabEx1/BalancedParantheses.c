#include "BalancedParantheses.h"

void push(Stack *stack, char value) {
    if (stack == NULL) {
        printf("Stack pointer is NULL\n");
        return;
    }
    if (stack->top >= MAX_SIZE - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack->data[++stack->top] = value;
}

char pop(Stack *stack) {
    if (stack == NULL) {
        printf("Stack pointer is NULL\n");
        return '\0';
    }
    if (stack->top < 0) {
        printf("Stack underflow\n");
        return '\0';
    }
    return stack->data[stack->top--];
}

bool isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

int checkExpression(const char expression[]) {
    if (expression == NULL) {
        printf("Expression pointer is NULL\n");
        return 0;
    }
    Stack stack = {.top = -1};
    size_t length = strlen(expression);

    for (size_t i = 0; i < length; i++) {
        char current = expression[i];

        if (current == '(' || current == '{' || current == '[') {
            push(&stack, current);
        } else if (current == ')' || current == '}' || current == ']') {
            if (stack.top < 0) {
                return 0;
            }
            char top = pop(&stack);
            if (!isMatchingPair(top, current) && top != '\0') {
                return 0;
            }
        }
    }

    // To stack πρεπει να ειναι αδειο για να ειναι ισορροπημενη η εκφραση
    if (stack.top >= 0) {
        return 0;
    }
    return 1;
}