# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def levelOrder(self, root: TreeNode) -> List[List[int]]:
        if not root:
            return []

        res = []
        queue = deque()
        queue.append(root)
        while len(queue):
            size = len(queue)
            level_nodes = []
            for i in range(size):
                curr = queue.popleft()
                level_nodes.append(curr.val)
                if curr.left:
                    queue.append(curr.left)
                if curr.right:
                    queue.append(curr.right)
            res.append(level_nodes)

        return res

    # 迭代 前序遍历
    def levelOrder2(self, root: TreeNode) -> List[List[int]]:
        if not root:
            return []

        res, stack = list(), list()
        stack.append([root, 0])
        while len(stack):
            curr_node, curr_level = stack.pop()

            if len(res) == curr_level:
                res.append([curr_node.val])
            else:
                res[curr_level].append(curr_node.val)

            if curr_node.right:
                stack.append([curr_node.right, curr_level + 1])
            if curr_node.left:
                stack.append([curr_node.left, curr_level + 1])
        return res

    # 递归 前序遍历
    def levelOrder(self, root: TreeNode) -> List[List[int]]:
        if not root:
            return []
        res = list()
        self.preorder(root, 0, res)
        return res

    def preorder(self, node: TreeNode, curr_level: int,  res: List[int]) -> None:
        if not node:
            return
        if len(res) == curr_level:
            res.append([node.val])
        else:
            res[curr_level].append(node.val)

        self.preorder(node.left, curr_level + 1, res)
        self.preorder(node.right, curr_level + 1, res)