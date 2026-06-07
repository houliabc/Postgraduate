// 抖码算法，让算法学习变的简单有趣
// 作者：老汤

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
 * @param {number} targetSum
 * @return {boolean}
 */
var hasPathSum = function(root, targetSum) {
    if (!root) return false
    if (!root.left && !root.right) {
        return targetSum - root.val == 0
    }

    const leftHasPathSum = hasPathSum(root.left, targetSum - root.val)
    if (leftHasPathSum) return true

    const rightHasPathSum = hasPathSum(root.right, targetSum - root.val)

    return leftHasPathSum || rightHasPathSum
};