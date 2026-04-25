input = input("Give a string containing the characters:'{','}','(',')','[',']'.")

def check_expression(expression):
    stack = []
    mapping = {")": "(", "]": "[", "}": "{"}

    for char in expression:
        if char in "([{":
            stack.append(char)
        elif char in "}])":
            
            if not stack or stack.pop() != mapping[char]:
                return 0
    return 1 if not stack else 0

print(f"Result: {check_expression(input)}")