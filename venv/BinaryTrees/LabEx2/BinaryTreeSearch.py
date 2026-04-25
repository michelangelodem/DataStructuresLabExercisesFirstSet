class Node:
    def __init__(self,key):
        self.left = None
        self.right = None
        self.val = key

    def __repr__(self):
        return f"Node(val={self.val}, height = {getHeight(self, 0)})"

def getHeight(root, h):
    if root is None:
        return h - 1
    return max(getHeight(root.left, h + 1), getHeight(root.right, h + 1))

def sortedArrayToBSTRecur(arr, start, end):
    if start > end:
        return None

    mid = start + (end - start) // 2
    root = Node(arr[mid])

    root.left = sortedArrayToBSTRecur(arr, start, mid - 1)
    root.right = sortedArrayToBSTRecur(arr, mid + 1, end)

    return root

def sortedArrayToBST(arr):
    return sortedArrayToBSTRecur(arr, 0, len(arr) - 1)

def binaryTreeSearch(root, key):
    if root is None:
        return None
    if root.val == key:
        return root
    
    if root.val<key:
        return binaryTreeSearch(root.right, key)
    elif root.val > key:
        return binaryTreeSearch(root.left, key)
  
if __name__ == "__main__":
    key = 3

    in_arr = [12,3,4,5,13]
    in_arr.sort() 
    BST = sortedArrayToBST(in_arr)
    print(f"Node: {binaryTreeSearch(BST, key)}\n")