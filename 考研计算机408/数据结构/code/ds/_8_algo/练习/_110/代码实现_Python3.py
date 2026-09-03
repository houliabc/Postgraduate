# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def isBalanced(self, root: TreeNode) -> bool:
        return self.maxDepth(root) >= 0

    # DFS 后序遍历 递归
    def maxDepth(self, root: TreeNode) -> int:
        if not root: return 0

        leftMaxDepth = self.maxDepth(root.left)
        rightMaxDepth = self.maxDepth(root.right)

        if leftMaxDepth == -1 or rightMaxDepth == -1 or abs(leftMaxDepth - rightMaxDepth) > 1:
            return -1

        return max(leftMaxDepth, rightMaxDepth) + 1