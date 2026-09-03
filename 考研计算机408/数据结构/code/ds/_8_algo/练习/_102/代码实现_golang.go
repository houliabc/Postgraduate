/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
// 层序遍历 - 队列实现
func levelOrder1(root *TreeNode) [][]int {
    if root == nil {
        return [][]int{}
    }

    var res = make([][]int, 0)
    // 用双向链表实现单向队列的功能
    var queue = list.New()
    queue.PushBack(root) // 入队(往链表表尾添加元素)
    for queue.Len() > 0 {
        // 每轮循环遍历处理一层的节点
        var size, levelNodes = queue.Len(), make([]int, 0)
        for i := 0; i < size; i++ {
            // 出队，删除并得到链表表头元素
            var curr = queue.Remove(queue.Front()).(*TreeNode)
            levelNodes = append(levelNodes, curr.Val)
            if curr.Left != nil {
                queue.PushBack(curr.Left)
            }
            if curr.Right != nil {
                queue.PushBack(curr.Right)
            }
        }
        res = append(res, levelNodes)
    }

    return res
}

type Node struct {
    node *TreeNode
    level int
}

// 前序遍历(迭代)实现层序遍历
func levelOrder2(root *TreeNode) [][]int {
    if root == nil {
        return [][]int{}
    }

    var res, stack = make([][]int, 0), make([]*Node, 0)
    stack = append(stack, &Node{node:root, level:0})
    for len(stack) > 0 {
        var node = stack[len(stack) - 1]
        stack = stack[:len(stack) - 1]

        var curr, currLevel = node.node, node.level
        if len(res) == currLevel {
            var levelNodes = make([]int, 0)
            levelNodes = append(levelNodes, curr.Val)
            res = append(res, levelNodes)
        } else {
            res[currLevel] = append(res[currLevel], curr.Val)
        }

        if curr.Right != nil {
            stack = append(stack, &Node{node:curr.Right, level:currLevel + 1})
        }
        if curr.Left != nil {
            stack = append(stack, &Node{node:curr.Left, level:currLevel + 1})
        }
    }

    return res
}


// 前序遍历(递归)实现层序遍历
func levelOrder(root *TreeNode) [][]int {
    var res = make([][]int, 0)

    var preOrder func(*TreeNode, int)
    preOrder = func(node *TreeNode, currLevel int) {
        if node == nil {
            return
        }
        if len(res) == currLevel {
            var levelNodes = make([]int, 0)
            levelNodes = append(levelNodes, node.Val)
            res = append(res, levelNodes)
        } else {
            res[currLevel] = append(res[currLevel], node.Val)
        }
        preOrder(node.Left, currLevel + 1)
        preOrder(node.Right, currLevel + 1)
    }

    preOrder(root, 0)

    return res
}