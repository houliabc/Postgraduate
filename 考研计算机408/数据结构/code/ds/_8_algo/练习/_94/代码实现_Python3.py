# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    # 迭代解法
    def inorderTraversal1(self, root: TreeNode) -> List[int]:
        if not root:
            return []
        res, stack = list(), list()
        curr = root
        while curr or len(stack):
            while curr:
                stack.append(curr)
                curr = curr.left
            node = stack.pop()
            res.append(node.val)
            curr = node.right
        return res

    # 递归解法
    def inorderTraversal(self, root: TreeNode) -> List[int]:
        if not root:
            return []
        res = list()
        self.inorder(root, res)
        return res

    def inorder(self, node: TreeNode, res: List[int]) -> None:
        if not node: return
        self.inorder(node.left, res)
        res.append(node.val)
        self.inorder(node.right, res)