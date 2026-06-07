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
 * @return {number[][]}
 */
var levelOrder = function(root) {
    if (!root) return []

    const res = [], queue = []
    queue.push(root)
    while (queue.length) {
        const size = queue.length
        const levelNodes = []
        for (let i = 0; i < size; i++) {
            const curr = queue.shift()
            levelNodes.push(curr.val)
            if (curr.left) queue.push(curr.left)
            if (curr.right) queue.push(curr.right)
        }
        res.push(levelNodes)
    }

    return res
};

// 迭代 前序遍历
var levelOrder2 = function(root) {
    if (!root) return []
    const stack = [], res = []
    stack.push([root, 0])
    while (stack.length) {
        const curr = stack.pop()
        const currNode = curr[0], currLevel = curr[1]
        if (res.length == currLevel) {
            res.push([currNode.val])
        } else {
            res[currLevel].push(currNode.val)
        }
        if (currNode.right) stack.push([currNode.right, currLevel + 1])
        if (currNode.left) stack.push([currNode.left, currLevel + 1])
    }
    return res
}

// 递归 前序遍历
var levelOrder = function(root) {
    if (!root) return []

    const preorder = (node, currLevel, res) => {
        if (!node) return
        if (res.length == currLevel) {
            res.push([node.val])
        } else {
            res[currLevel].push(node.val)
        }
        preorder(node.left, currLevel + 1, res)
        preorder(node.right, currLevel + 1, res)
    }

    const res = []
    preorder(root, 0, res)
    return res
}