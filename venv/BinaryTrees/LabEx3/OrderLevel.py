from queue import Queue
import math

class Node:
    def __init__(self,key):
        self.left = None
        self.right = None
        self.val = key
        self.index = 0

    def __repr__(self):
        return f"Node(val={self.val}, height = {getHeight(self)}, level = {getLevel(self)})"

def getLevel(root):
    return int(math.log(root.index,2))

def getHeight(root):
    if root is None:
        return -1
    left_height = getHeight(root.left)
    right_height = getHeight(root.right)
    
    return 1 + max(left_height, right_height)

def arrayToTree(arr):
    if not arr:
            return None
        
    nodes = [Node(val) for val in arr]
        
    for i in range(len(nodes)):
        left_idx = 2 * i + 1
        right_idx = 2 * i + 2
        nodes[i].index = i + 1
        
        if left_idx < len(nodes):
            nodes[i].left = nodes[left_idx]
        if right_idx < len(nodes):
            nodes[i].right = nodes[right_idx]
            
    return nodes[0]    

def levelOrder(root):
    if root is None: 
        return 
    q = Queue() 
    q.put(root)

    while not q.empty():
        current_node = q.get() 
        print(f"\n{current_node}\n") 

        if current_node.left: 
            q.put(current_node.left)
        if current_node.right: 
            q.put(current_node.right)

if __name__ == "__main__":
    arr = [12,32,11,43,6,58,3,65,9]
    root = arrayToTree(arr)
    levelOrder(root)