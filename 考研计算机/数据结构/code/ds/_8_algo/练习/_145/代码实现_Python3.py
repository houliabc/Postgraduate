# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    # 迭代解法
    def postorderTraversal1(self, root: TreeNode) -> List[int]:
        if not root: return []

        res, stack = list(), list()
        stack.append(root)
        while len(stack):
            curr = stack.pop()
            res.append(curr.val)
            if curr.left:
                stack.append(curr.left)
            if curr.right:
                stack.append(curr.right)
        res.reverse()
        return res

    # 递归解法
    def postorderTraversal(self, root: TreeNode) -> List[int]:
        if not root: return []
        res = list()
        self.postorder(root, res)
        return res

    def postorder(self, node: TreeNode, res: List[int]) -> None:
        if not node:
            return
        self.postorder(node.left, res)
        self.postorder(node.right, res)
        res.append(node.val)