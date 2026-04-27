#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int top;
    char data[MAX_SIZE];
} Stack;

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


int main(void) {
    const char* def = "{3x(2+5)/[4-{(3-1)x2}]}";
    int result = checkExpression(def);
    printf("Expression: %s | Balanced: %s\n", def, result == 1 ? "Yes" : "No");
}

// =================================================================================
// =============================  TEST FOR BALANCED PARENTHESES  ===================
// =================================================================================
// Uncomment τον παρακάτω κώδικα για να τρέξετε τα tests 
// και comment out τη main() παραπάνω.

// void runTest(const char* expression, int testNum) {
//     bool result = checkExpression(expression);
//     int output = result? 1 : 0;

//     printf("Test 1.%2d | Got: %d => %s| Input: \"%s\"\n", 
//            testNum, output, output == 1 ? "Balanced" : "Not Balanced", expression);
// }

// int main(void) {
//     runTest("", 1);                      
//     runTest("(", 2);                   
//     runTest(")", 3);                      
//     runTest(")(", 4);                  
//     runTest("(((", 5);                    
//     runTest(")))", 6);                    
//     runTest("([)]", 7);                  
//     runTest("({[}])", 8);                
//     runTest("[[[[]]]]", 9);             
//     runTest("{{{{}}}", 10);              
    
//     runTest("()", 11);                   
//     runTest("{}", 12);                 
//     runTest("[]", 13);                 
//     runTest("([])", 14);              
//     runTest("({[]})", 15);        
//     runTest("{[()]}", 16);              
    
//     runTest("(){}[]", 17);              
//     runTest("()[]{}", 18);               
//     runTest("()()()", 19);             
//     runTest("{{}}(())", 20);            
//     runTest("[(){}]", 21);                
    
//     runTest("(]", 22);                   
//     runTest("(}", 23);                  
//     runTest("[)", 24);                   
//     runTest("{]", 25);                   
//     runTest("([]}", 26);                  
//     runTest("{[)]}", 27);                
    
//     runTest("((())", 28);                
//     runTest("(())))", 29);                
//     runTest("(()())", 30);                
//     runTest("()((", 31);                 
//     runTest(")()((", 32);                 
    
//     runTest("(((())))", 33);             
//     runTest("[{()}]", 34);                
//     runTest("({[({[({[", 35);            
//     runTest("]})]})({", 36);             
//     return 0;
// }