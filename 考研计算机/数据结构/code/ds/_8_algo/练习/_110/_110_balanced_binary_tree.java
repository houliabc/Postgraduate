package com.douma._16_day_二叉树一._110;

import com.douma._16_day_二叉树一.TreeNode;

/**
 * 高频算法面试题
 *      力扣 110. 平衡二叉树
 */
public class _110_balanced_binary_tree {
    /*  110. 平衡二叉树
        给定一个二叉树，判断它是否是高度平衡的二叉树。
        本题中，一棵高度平衡二叉树定义为：
            一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1 。

        输入：
              1
             / \
            2   3
           / \
          4   5
        输出：true

        输入：
              1
             / \
            2   3
           / \
          4   5
         / \
        6   7
        输出：false
     */

    public boolean isBalanced(TreeNode root) {
        return maxDepth(root) >= 0;
    }

    // DFS 递归 - 后序遍历
    // 计算以 root 为根节点的二叉树的最大深度
    public int maxDepth(TreeNode root) {
        if (root == null) return 0;
        int leftMaxDepth = maxDepth(root.left);
        int rightMaxDepth = maxDepth(root.right);

        if (leftMaxDepth == -1 || rightMaxDepth == -1) {
            return -1;
        }

        if (Math.abs(leftMaxDepth - rightMaxDepth) > 1) {
            return -1;
        }

        // 处理根节点
        return Math.max(leftMaxDepth, rightMaxDepth) + 1;
    }
}
