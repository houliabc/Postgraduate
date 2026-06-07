/**
 * Definition for a binary tree node.
 * function TreeNode(val, left, right) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.left = (left===undefined ? null : left)
 *     this.right = (right===undefined ? null : right)
 * }
 */
/**
 * @param {TreeNode} root
 * @return {number[]}
 */
// 迭代解法
var preorderTraversal = function(root) {
    if (!root) return []
    const stack = [], res = []
    stack.push(root)
    while (stack.length) {
        const curr = stack.pop()
        res.push(curr.val)
        if (curr.right) stack.push(curr.right)
        if (curr.left) stack.push(curr.left)
    }
    return res
};

// 递归解法
var preorderTraversal = function(root) {
    if (!root) return []

    const preorder = (node, res) => {
        if (!node) return
        res.push(node.val)
        preorder(node.left, res)
        preorder(node.right, res)
    }

    const res = []
    preorder(root, res)
    return res
}