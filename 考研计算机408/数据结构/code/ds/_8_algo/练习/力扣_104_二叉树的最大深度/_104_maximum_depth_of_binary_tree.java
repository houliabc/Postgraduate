package com.laotang.第_9_章_二叉树.力扣_104_二叉树的最大深度;


import com.laotang.第_9_章_二叉树.TreeNode;

import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;

/**
 * @官方网站 : https://douma.ke.qq.com
 * @微信公众号 : 抖码课堂
 * @官方微信号 : bigdatatang01
 * 抖码算法，让算法学习变的简单有趣
 * @作者 : 老汤
 */
public class _104_maximum_depth_of_binary_tree {
    /* 104. 二叉树的最大深度
       给定一个二叉树，找出其最大深度。
       二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。
       说明: 叶子节点是指没有子节点的节点。

       输入：
            3
           / \
          9  20
            /  \
           15   7
       输出：3
     */

    // 层序遍历(BFS)
    public int maxDepth1(TreeNode root) {
        if (root == null) return 0;

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        int levels = 0;
        while (!queue.isEmpty()) {
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                TreeNode curr = queue.poll();
                if (curr.left != null) queue.offer(curr.left);
                if (curr.right != null) queue.offer(curr.right);
            }
            levels++;
        }
        return levels;
    }

    private class Node {
        TreeNode node;
        int depth;

        Node(TreeNode node, int depth) {
            this.node = node;
            this.depth = depth;
        }
    }

    // DFS 迭代 - 前序遍历
    public int maxDepth2(TreeNode root) {
        if (root == null) return 0;

        int res = 0;
        Stack<Node> stack = new Stack<>();
        stack.push(new Node(root, 1));
        while (!stack.isEmpty()) {
            Node node = stack.pop();
            TreeNode curr = node.node;
            int currDepth = node.depth;

            if (curr.left == null && curr.right == null) {
                res = Math.max(res, currDepth);
            }

            if (curr.right != null) {
                stack.push(new Node(curr.right, currDepth + 1));
            }

            if (curr.left != null) {
                stack.push(new Node(curr.left, currDepth + 1));
            }
        }

        return res;
    }

    // DFS 递归 - 前序遍历
    private int res = 0;
    public int maxDepth3(TreeNode root) {
        preorder(root, 1);
        return res;
    }

    private void preorder(TreeNode node, int depth) {
        if (node == null) return;
        // 处理当前的节点
        if (node.left == null && node.right == null) {
            res = Math.max(res, depth);
        }

        preorder(node.left, depth + 1);
        preorder(node.right, depth + 1);
    }

    // DFS 递归 - 后序遍历
    // 计算以 root 为根节点的二叉树的最大深度
    public int maxDepth(TreeNode root) {
        if (root == null) return 0;
        int leftMaxDepth = maxDepth(root.left);
        int rightMaxDepth = maxDepth(root.right);

        // 处理根节点
        return Math.max(leftMaxDepth, rightMaxDepth) + 1;
    }
}
