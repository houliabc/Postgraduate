# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def __init__(self):
        self.res = 0

    # BFS
    def maxDepth1(self, root: TreeNode) -> int:
        if not root: return 0

        res, queue = 0, deque()
        queue.append(root)
        while len(queue):
            size = len(queue)
            for i in range(size):
                curr = queue.popleft()
                if curr.left:
                    queue.append(curr.left)
                if curr.right:
                    queue.append(curr.right)
            res += 1

        return res

    # DFS 前序遍历
    def maxDepth2(self, root: TreeNode) -> int:
        if not root: return 0

        res, stack = 0, list()
        stack.append([root, 1])
        while len(stack):
            curr_node, curr_level = stack.pop()

            res = max(res, curr_level)

            if curr_node.right:
                stack.append([curr_node.right, curr_level + 1])
            if curr_node.left:
                stack.append([curr_node.left, curr_level + 1])

        return res

    # DFS 前序遍历 递归
    def maxDepth3(self, root: TreeNode) -> int:
        if not root: return 0
        self.preorder(root, 1)
        return self.res

    def preorder(self, node: TreeNode, curr_level: int) -> None:
        if not node: return

        self.res = max(self.res, curr_level)

        self.preorder(node.left, curr_level + 1)
        self.preorder(node.right, curr_level + 1)


    # DFS 后序遍历 递归
    def maxDepth(self, root: TreeNode) -> int:
        if not root: return 0

        leftMaxDepth = self.maxDepth(root.left)
        rightMaxDepth = self.maxDepth(root.right)

        return max(leftMaxDepth, rightMaxDepth) + 1