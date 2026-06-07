# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def zigzagLevelOrder(self, root: TreeNode) -> List[List[int]]:
        if not root:
            return []

        res, queue, from_right_to_left = [], deque(), False
        queue.append(root)
        while len(queue):
            size = len(queue)
            # 因为我们已经知道了这一层有多少个节点，所以可以固定数组大小
            level_nodes = [0] * size
            for i in range(size):
                curr = queue.popleft()
                # 如果是从右往左的话，那么将节点值从后往前放，否则从前往后放
                index = (size - i - 1) if from_right_to_left else i
                level_nodes[index] = curr.val
                if curr.left:
                    queue.append(curr.left)
                if curr.right:
                    queue.append(curr.right)
            res.append(level_nodes)
            from_right_to_left = not from_right_to_left

        return res