/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
// 迭代解法
func inorderTraversal1(root *TreeNode) []int {
    if root == nil {
        return []int{}
    }

    var res, stack = make([]int, 0), make([]*TreeNode, 0)
    var curr = root
    for curr != nil || len(stack) > 0 {
        for curr != nil {
            stack = append(stack, curr)
            curr = curr.Left
        }
        var node = stack[len(stack) - 1]
        stack = stack[:len(stack) - 1]
        res = append(res, node.Val)

        curr = node.Right
    }

    return res
}

// 递归解法
func inorderTraversal(root *TreeNode) []int {
    var res = make([]int, 0)

    var inOrder func(*TreeNode)
    inOrder = func(node *TreeNode) {
        if node == nil {
            return
        }
        inOrder(node.Left)
        res = append(res, node.Val)
        inOrder(node.Right)
    }

    inOrder(root)
    return res
}