def find_celebrity(mat):
    m_len = len(mat)
    stack = []
    print(f"#Of all suspects: {m_len}")

    for i in range(m_len):
        stack.append(i)

    while(len(stack)>1):
        #o celebrity δεν ξερει κανεναν αλλα ολοι τον ξερουν.

        canditate1 = stack.pop()
        canditate2 = stack.pop()

        if(mat[canditate1][canditate2] == 1):
            stack.append(canditate2)
            print(f"\n{canditate1+1} not a celebrity because he knows {canditate2+1}.\n")
        elif(not mat[canditate1][canditate2]):
            stack.append(canditate1)
            print(f"\n{canditate2+1} not a celebrity because he knows {canditate1+1}.\n")

    celeb = stack.pop()
    print(f"\nLast possible celebrity: {celeb+1}\n")

    for i in range(m_len):
        if(i!=celeb and (not mat[celeb][i]==1 or mat[i][celeb])):
            print(f"\n{celeb+1} not a celebrity after all\n")            
            return -1
    return celeb+1    

if __name__ == "__main__":
    in_matrix = [[1,0,0,0,1],
                 [1,1,1,0,0],
                 [1,0,1,1,1],
                 [0,0,0,1,1],
                 [1,0,1,1,1]]

    print(f"Index of celebrity: {find_celebrity(in_matrix)}" if find_celebrity(in_matrix)!=-1 else f"No celebrity found")