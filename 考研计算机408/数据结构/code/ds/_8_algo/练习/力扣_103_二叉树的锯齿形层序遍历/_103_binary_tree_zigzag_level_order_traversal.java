package com.laotang.第_9_章_二叉树.力扣_103_二叉树的锯齿形层序遍历;

import com.laotang.第_9_章_二叉树.TreeNode;

import java.util.*;

/**
 * @官方网站 : https://douma.ke.qq.com
 * @微信公众号 : 抖码课堂
 * @官方微信号 : bigdatatang01
 * 抖码算法，让算法学习变的简单有趣
 * @作者 : 老汤
 */
public class _103_binary_tree_zigzag_level_order_traversal {
    /* 103. 二叉树的锯齿形层序遍历
    给定一个二叉树，返回其节点值的锯齿形层序遍历。
    （即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。

    输入：
        3
       / \
      9  20
        /  \
       15   7
   输出：
    [
        [3],
        [20,9]
        [15,7]
    ]
     */

    // BFS
    public List<List<Integer>> zigzagLevelOrder1(TreeNode root) {
        List<List<Integer>> res = new ArrayList<>();
        if (root == null) return res;

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        boolean fromRight = false;
        while (!queue.isEmpty()) {
            // 每轮循环遍历处理一层的节点
            int size = queue.size();
            Integer[] levelNodes = new Integer[size];
            for (int i = 0; i < size; i++) {
                TreeNode curr = queue.poll();
                // 如果是从右往左的话，那么将节点值从后往前放，否则从前往后放
                if (fromRight) {
                    levelNodes[size - 1 - i] = curr.val;
                } else {
                    levelNodes[i] = curr.val;
                }
                if (curr.left != null) queue.offer(curr.left);
                if (curr.right != null) queue.offer(curr.right);
            }
            res.add(Arrays.asList(levelNodes));
            fromRight = !fromRight;
        }

        return res;
    }

    // 前序遍历(递归)实现层序遍历
    public List<List<Integer>> zigzagLevelOrder(TreeNode root) {
        List<List<Integer>> res = new ArrayList<>();
        preorder(root, 0, res);
        return res;
    }

    private void preorder(TreeNode node, int currLevel, List<List<Integer>> res) {
        if (node == null) return;

        // 处理当前遍历的节点
        if (res.size() == currLevel) {
            List<Integer> levelNodes = new LinkedList<>();
            res.add(levelNodes);
        }

        List<Integer> levelNodes = res.get(currLevel);
        if (currLevel % 2 == 0) levelNodes.add(node.val);
        else levelNodes.add(0, node.val);

        preorder(node.left, currLevel + 1, res);
        preorder(node.right, currLevel + 1, res);
    }
}
