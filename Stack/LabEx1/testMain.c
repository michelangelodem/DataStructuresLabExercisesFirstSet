#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "BalancedParantheses.h"

// =================================================================================
// =============================  TEST FOR BALANCED PARENTHESES  ===================
// =================================================================================

void runTest(const char* expression, int testNum) {
    bool result = checkExpression(expression);
    int output = result? 1 : 0;

    printf("Test 1.%2d | Got: %d => %s| Input: \"%s\"\n", 
           testNum, output, output == 1 ? "Balanced" : "Not Balanced", expression);
}

int main(void) {
    runTest("", 1);                      
    runTest("(", 2);                   
    runTest(")", 3);                      
    runTest(")(", 4);                  
    runTest("(((", 5);                    
    runTest(")))", 6);                    
    runTest("([)]", 7);                  
    runTest("({[}])", 8);                
    runTest("[[[[]]]]", 9);             
    runTest("{{{{}}}", 10);              
    
    runTest("()", 11);                   
    runTest("{}", 12);                 
    runTest("[]", 13);                 
    runTest("([])", 14);              
    runTest("({[]})", 15);        
    runTest("{[()]}", 16);              
    
    runTest("(){}[]", 17);              
    runTest("()[]{}", 18);               
    runTest("()()()", 19);             
    runTest("{{}}(())", 20);            
    runTest("[(){}]", 21);                
    
    runTest("(]", 22);                   
    runTest("(}", 23);                  
    runTest("[)", 24);                   
    runTest("{]", 25);                   
    runTest("([]}", 26);                  
    runTest("{[)]}", 27);                
    
    runTest("((())", 28);                
    runTest("(())))", 29);                
    runTest("(()())", 30);                
    runTest("()((", 31);                 
    runTest(")()((", 32);                 
    
    runTest("(((())))", 33);             
    runTest("[{()}]", 34);                
    runTest("({[({[({[", 35);            
    runTest("]})]})({", 36);             
    return 0;
}