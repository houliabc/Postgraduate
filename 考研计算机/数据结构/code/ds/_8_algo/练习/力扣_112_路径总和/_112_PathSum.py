class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    # DFS 递归
    def hasPathSum(self, root: TreeNode, targetSum: int) -> bool:
        if not root:
            return False
        # 如果当前节点是叶子，检查 sum 值是否为 0，也就是是否找到了给定的目标和。
        if not root.left and not root.right:
            return targetSum - root.val == 0
        # 如果当前节点不是叶子，对它的所有孩子节点，递归调用 hasPathSum 函数，
        # 其中 sum 值减去当前节点的权值
        left_has_path_sum = self.hasPathSum(root.left, targetSum - root.val)
        right_has_path_sum = self.hasPathSum(root.right, targetSum - root.val)
        return left_has_path_sum or right_has_path_sum

    # DFS 迭代
    def hasPathSum1(self, root: TreeNode, targetSum: int) -> bool:
        if not root:
            return False
        stack = [(root, targetSum - root.val)]
        while len(stack) > 0:
            curr_node, curr_path_remain_sum = stack.pop()
            # 如果当前节点为叶子节点，且当前节点的路径和等于目标和，则直接返回 true
            if not curr_node.left and not curr_node.right and curr_path_remain_sum == 0:
                return True
            if curr_node.right:
                stack.append((curr_node.right, curr_path_remain_sum - curr_node.right.val))
            if curr_node.left:
                stack.append((curr_node.left, curr_path_remain_sum - curr_node.left.val))
        return False