package com.douma._16_day_二叉树一._144;

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
public class _144_binary_tree_preorder_traversal {
    /* 144. 二叉树的前序遍历
    给你二叉树的根节点 root ，返回它节点值的 前序 遍历。

     */





    // 迭代解法
    public List<Integer> preorderTraversal1(TreeNode root) {
        ArrayList<Integer> res = new ArrayList<>();
        if (root ==null) return res;

        Stack<TreeNode> stack = new Stack<>();
        stack.push(root);

        while (!stack.isEmpty()) {
            TreeNode curr = stack.pop();
            res.add(curr.val);
            if (curr.right != null) stack.push(curr.right);
            if (curr.left != null) stack.push(curr.left);
        }
        return res;
    }

    // 递归解法
    public List<Integer> preorderTraversal(TreeNode root) {
        ArrayList<Integer> res = new ArrayList<>();
        if (root ==null) return res;
        preOrder(root, res);
        return res;
    }

    private void preOrder(TreeNode node, List<Integer> res) {
        if (node == null) return;
        // 处理当前遍历的节点
        res.add(node.val);
        preOrder(node.left, res);
        preOrder(node.right, res);
    }
}
