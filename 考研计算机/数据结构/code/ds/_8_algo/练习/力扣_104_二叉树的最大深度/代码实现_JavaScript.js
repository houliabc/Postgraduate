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
 * @return {number}
 */
// BFS
var maxDepth1 = function(root) {
    if (!root) return 0

    let res = 0
    const queue = []
    queue.push(root)
    while (queue.length) {
        const size = queue.length
        for (let i = 0; i < size; i++) {
            const curr = queue.shift();
            if (curr.left) queue.push(curr.left)
            if (curr.right) queue.push(curr.right)
        }
        res++
    }

    return res
};

// DFS 前序遍历
var maxDepth2 = function(root) {
    if (!root) return 0
    let res = 0
    const stack = []
    stack.push([root, 1])
    while (stack.length) {
        const curr = stack.pop()
        const currNode = curr[0], currLevel = curr[1]
        res = Math.max(res, currLevel)
        if (currNode.right) stack.push([currNode.right, currLevel + 1])
        if (currNode.left) stack.push([currNode.left, currLevel + 1])
    }
    return res
}

// DFS 前序遍历 递归
var maxDepth3 = function(root) {
    if (!root) return 0
    let res = 0
    const preorder = (node, currLevel) => {
        if (!node) return
        res = Math.max(res, currLevel)
        preorder(node.left, currLevel + 1)
        preorder(node.right, currLevel + 1)
    }

    preorder(root, 1)
    return res
}

// DFS 后序遍历 递归
var maxDepth = function(root) {
    if (!root) return 0

    const leftMaxDepth = maxDepth(root.left)
    const rightMaxDepth = maxDepth(root.right)

    return Math.max(leftMaxDepth, rightMaxDepth) + 1
}