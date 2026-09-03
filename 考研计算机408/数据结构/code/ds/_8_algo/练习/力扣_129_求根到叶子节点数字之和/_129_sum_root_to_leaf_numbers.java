package com.laotang.第_9_章_二叉树.力扣_129_求根到叶子节点数字之和;

import com.laotang.第_9_章_二叉树.TreeNode;

public class _129_sum_root_to_leaf_numbers {

    int res = 0;
    public int sumNumbers(TreeNode root) {
       return postOrder(root, 0);
    }

    // 后序遍历
    private int postOrder(TreeNode node, int prevNum) {
        if (node == null) return 0;

        if (node.left == null && node.right == null) {
            return prevNum * 10 + node.val;
        }

        int num1 = postOrder(node.left, prevNum * 10 + node.val);
        int num2 = postOrder(node.right, prevNum * 10 + node.val);

        return num1 + num2;
    }

    // 前序遍历
    private void preOrder(TreeNode node, int prevNum) {
        if (node == null) return;

        if (node.left == null && node.right == null) {
            res += prevNum * 10 + node.val;
            return;
        }

        preOrder(node.left, prevNum * 10 + node.val);
        preOrder(node.right, prevNum * 10 + node.val);
    }

}
