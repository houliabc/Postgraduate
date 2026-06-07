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
var postorderTraversal1 = function(root) {
    if (!root) return []

    const res = [], stack = []
    stack.push(root)
    while (stack.length) {
        const curr = stack.pop();
        res.push(curr.val)
        if (curr.left) stack.push(curr.left)
        if (curr.right) stack.push(curr.right)
    }
    res.reverse()
    return res
};

// 迭代解法
var postorderTraversal = function(root) {
    if (!root) return []

    const postorder = (node, res) => {
        if (!node) return
        postorder(node.left, res)
        postorder(node.right, res)
        res.push(node.val)
    }

    res = []
    postorder(root, res)
    return res
}