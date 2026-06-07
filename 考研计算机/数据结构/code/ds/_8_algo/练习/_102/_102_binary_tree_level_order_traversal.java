package com.douma._16_day_二叉树一._102;

import com.douma._16_day_二叉树一.TreeNode;

import java.util.*;

/**
 * @官方网站 : https://douma.ke.qq.com
 * @微信公众号 : 抖码课堂
 * @官方微信号 : bigdatatang01
 * 抖码算法，让算法学习变的简单有趣
 * @作者 : 老汤
 */
public class _102_binary_tree_level_order_traversal {
    /* 102. 二叉树的层序遍历
        给你一个二叉树，请你返回其按 层序遍历 得到的节点值。
        （即逐层地，从左到右访问所有节点）。
     */


    // 层序遍历
    public List<List<Integer>> levelOrder1(TreeNode root) {
        List<List<Integer>> res = new ArrayList<>();
        if (root == null) return res;

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        while (!queue.isEmpty()) {
            // 每轮循环遍历处理一层的节点
            int size = queue.size();
            List<Integer> levelNodes = new ArrayList<>();
            for (int i = 0; i < size; i++) {
                TreeNode curr = queue.poll();
                levelNodes.add(curr.val);
                if (curr.left != null) queue.offer(curr.left);
                if (curr.right != null) queue.offer(curr.right);
            }
            res.add(levelNodes);
        }

        return res;
    }

    private class Node {
        TreeNode node;
        int level;

        Node(TreeNode node, int level) {
            this.node = node;
            this.level = level;
        }
    }

    // 前序遍历(迭代)实现层序遍历
    public List<List<Integer>> levelOrder2(TreeNode root) {
        List<List<Integer>> res = new ArrayList<>();
        if (root == null) return res;

        Stack<Node> stack = new Stack<>();
        stack.push(new Node(root, 0));
        while (!stack.isEmpty()) {
            Node node = stack.pop();
            TreeNode curr = node.node;
            int currLevel = node.level;

            if (res.size() == currLevel) {
                List<Integer> levelNodes = new ArrayList<>();
                levelNodes.add(curr.val);
                res.add(levelNodes);
            } else {
                res.get(currLevel).add(curr.val);
            }

            if (curr.right != null) {
                stack.push(new Node(curr.right, currLevel + 1));
            }
            if (curr.left != null) {
                stack.push(new Node(curr.left, currLevel + 1));
            }
        }

        return res;
    }

    // 前序遍历(递归)实现层序遍历
    public List<List<Integer>> levelOrder(TreeNode root) {
        List<List<Integer>> res = new ArrayList<>();
        preorder(root, 0, res);
        return res;
    }

    private void preorder(TreeNode node, int currLevel, List<List<Integer>> res) {
        if (node == null) return;

        // 处理当前遍历的节点
        if (res.size() == currLevel) {
            List<Integer> levelNodes = new ArrayList<>();
            levelNodes.add(node.val);
            res.add(levelNodes);
        } else {
            res.get(currLevel).add(node.val);
        }

        preorder(node.left, currLevel + 1, res);
        preorder(node.right, currLevel + 1, res);
    }
}
