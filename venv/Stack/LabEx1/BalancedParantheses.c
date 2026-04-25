#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int top;
    char data[MAX_SIZE];
} Stack;

void push(Stack *stack, char value) {
    if (stack->top >= MAX_SIZE - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack->data[++stack->top] = value;
}

char pop(Stack *stack) {
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

bool checkExpression(const char expression[]) {
    Stack stack = {.top = -1};
    size_t length = strlen(expression);

    for (size_t i = 0; i < length; i++) {
        char current = expression[i];

        if (current == '(' || current == '{' || current == '[') {
            push(&stack, current);
        } else if (current == ')' || current == '}' || current == ']') {
            if (stack.top < 0) {
                return false;
            }
            char top = pop(&stack);
            if (!isMatchingPair(top, current)) {
                return false;
            }
        }
    }

    return stack.top == -1;
}

int main(void) {
    const char expression[] = "({[]})()";
    bool valid = checkExpression(expression);

    printf("%d\n", valid ? 1 : 0);
    return 0;
}