/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func isBalanced(root *TreeNode) bool {

    var maxDepth func(*TreeNode) int
    maxDepth = func(node *TreeNode) int {
        if node == nil {
            return 0
        }

        var leftMaxDepth = maxDepth(node.Left)
        var rightMaxDepth = maxDepth(node.Right)

        if leftMaxDepth == -1 || rightMaxDepth == -1 {
            return -1
        }

        if abs(leftMaxDepth - rightMaxDepth) > 1 {
            return -1
        }

        if (leftMaxDepth > rightMaxDepth) {
            return leftMaxDepth + 1
        } else {
            return rightMaxDepth + 1
        }
    }

    return maxDepth(root) >= 0
}

func abs(a int) int {
    if a < 0 {
        return -a
    }
    return a
}