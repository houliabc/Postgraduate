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
var zigzagLevelOrder = function(root) {
    if (!root) return []

    const res = [], queue = []
    queue.push(root)
    let fromRightToLeft = false
    while (queue.length) {
        const size = queue.length
        // 因为我们已经知道了这一层有多少个节点，所以可以使用数组
        const levelNodes = new Array(size).fill(0)
        for (let i = 0; i < size; i++) {
            const curr = queue.shift();
            // 如果是从右往左的话，那么将节点值从后往前放，否则从前往后放
            const index = fromRightToLeft ? (size - i - 1) : i
            levelNodes[index] = curr.val
            if (curr.left) queue.push(curr.left)
            if (curr.right) queue.push(curr.right)
        }
        res.push(levelNodes)
        fromRightToLeft = !fromRightToLeft
    }

    return res
};