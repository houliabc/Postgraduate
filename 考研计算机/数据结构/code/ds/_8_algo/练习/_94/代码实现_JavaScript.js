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
var inorderTraversal1 = function(root) {
    if (!root) return []
    const res = [], stack = []
    let curr = root
    while (curr || stack.length) {
        while (curr) {
            stack.push(curr)
            curr = curr.left
        }
        const node = stack.pop()
        res.push(node.val)
        curr = node.right
    }
    return res
};

// 递归解法
var inorderTraversal = function(root) {
    if (!root) return []

    const inorder = (node, res) => {
        if (!node) return
        inorder(node.left, res)
        res.push(node.val)
        inorder(node.right, res)
    }

    const res = []
    inorder(root, res)
    return res
}