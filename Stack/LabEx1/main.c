#include <stdio.h>
#include <string.h>
#include "BalancedParentheses.h"


int main(void) {
    const char* def = "{3x(2+5)/[4-{(3-1)x2}]}";
    int result = checkExpression(def);
    printf("Expression: %s | Balanced: %s\n", def, result == 1 ? "Yes" : "No");
}