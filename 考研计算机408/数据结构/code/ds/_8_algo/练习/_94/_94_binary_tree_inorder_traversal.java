package com.douma._16_day_二叉树一._94;

import com.douma._16_day_二叉树一.TreeNode;

import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

/**
 * @官方网站 : https://douma.ke.qq.com
 * @微信公众号 : 抖码课堂
 * @官方微信号 : bigdatatang01
 * 抖码算法，让算法学习变的简单有趣
 * @作者 : 老汤
 */
public class _94_binary_tree_inorder_traversal {
    /* 94. 二叉树的中序遍历
    给定一个二叉树的根节点 root ，返回它的 中序 遍历。
     */











    // 迭代解法
    public List<Integer> inorderTraversal1(TreeNode root) {
        List<Integer> res = new ArrayList<>();
        if (root == null) return res;

        Stack<TreeNode> stack = new Stack<>();
        TreeNode curr = root;
        while (curr != null || !stack.isEmpty()) {
            while (curr != null) {
                stack.push(curr);
                curr = curr.left;
            }
            TreeNode node = stack.pop();
            res.add(node.val);

            curr = node.right;
        }
        return res;
    }

    // 递归解法
    public List<Integer> inorderTraversal(TreeNode root) {
        List<Integer> res = new ArrayList<>();
        if (root == null) return res;
        inorder(root, res);
        return res;
    }

    private void inorder(TreeNode node, List<Integer> res) {
        if (node == null) return;
        inorder(node.left, res);
        res.add(node.val);
        inorder(node.right, res);
    }
}
