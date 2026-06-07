# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    # 迭代解法
    def preorderTraversal1(self, root: TreeNode) -> List[int]:
        if not root:
            return []
        res, stack = list(), list()
        stack.append(root)
        while len(stack):
            curr = stack.pop()
            res.append(curr.val)
            if curr.right:
                stack.append(curr.right)
            if curr.left:
                stack.append(curr.left)
        return res

    # 递归解法
    def preorderTraversal(self, root: TreeNode) -> List[int]:
        if not root:
            return []
        res = list()
        self.preorder(root, res)
        return res

    def preorder(self, node: TreeNode, res: List[int]) -> None:
        if not node:
            return
        res.append(node.val)
        self.preorder(node.left, res)
        self.preorder(node.right, res)