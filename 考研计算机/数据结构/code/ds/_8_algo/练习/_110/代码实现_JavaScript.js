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
 * @return {boolean}
 */
var isBalanced = function(root) {

    const maxDepth = (node) => {
        if (!node) return 0
        const leftMaxDepth = maxDepth(node.left)
        const rightMaxDepth = maxDepth(node.right)
        if (leftMaxDepth == -1 ||
                rightMaxDepth == -1 ||
                Math.abs(leftMaxDepth - rightMaxDepth) > 1) {
            return -1
        }
        return Math.max(leftMaxDepth, rightMaxDepth) + 1
    }

    return maxDepth(root) >= 0
};