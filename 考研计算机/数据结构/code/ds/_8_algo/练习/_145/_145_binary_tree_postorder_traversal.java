package com.douma._16_day_二叉树一._145;

import com.douma._16_day_二叉树一.TreeNode;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Stack;

/**
 * @官方网站 : https://douma.ke.qq.com
 * @微信公众号 : 抖码课堂
 * @官方微信号 : bigdatatang01
 * 抖码算法，让算法学习变的简单有趣
 * @作者 : 老汤
 */
public class _145_binary_tree_postorder_traversal {
    /* 145. 二叉树的后序遍历
    给定一个二叉树，返回它的 后序 遍历。
     */














    // 迭代解法
    public List<Integer> postorderTraversal1(TreeNode root) {
        LinkedList<Integer> res = new LinkedList<>();
        if (root ==null) return res;

        Stack<TreeNode> stack = new Stack<>();
        stack.push(root);

        while (!stack.isEmpty()) {
            TreeNode curr = stack.pop();
            res.addFirst(curr.val);
            if (curr.left != null) stack.push(curr.left);
            if (curr.right != null) stack.push(curr.right);
        }
        return res;
    }

    // 递归解法
    public List<Integer> postorderTraversal(TreeNode root) {
        List<Integer> res = new ArrayList<>();
        if (root ==null) return res;
        postorder(root, res);
        return res;
    }

    private void postorder(TreeNode node, List<Integer> res) {
        if (node == null) return;
        postorder(node.left, res);
        postorder(node.right, res);
        res.add(node.val);
    }
}
