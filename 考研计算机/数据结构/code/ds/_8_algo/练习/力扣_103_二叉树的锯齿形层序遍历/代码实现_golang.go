/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
// BFS
func zigzagLevelOrder1(root *TreeNode) [][]int {
    if root == nil {
        return [][]int{}
    }

    var res = make([][]int, 0)
    // 用双向链表实现单向队列的功能
    var queue = list.New()
    queue.PushBack(root) // 入队(往链表表尾添加元素)
    var fromRight = false
    for queue.Len() > 0 {
        // 每轮循环遍历处理一层的节点
        var size, levelNodes = queue.Len(), make([]int, queue.Len())
        for i := 0; i < size; i++ {
            // 出队，删除并得到链表表头元素
            var curr = queue.Remove(queue.Front()).(*TreeNode)
            // 如果是从右往左的话，那么将节点值从后往前放，否则从前往后放
            if fromRight {
                levelNodes[size - 1 - i] = curr.Val
            } else {
                levelNodes[i] = curr.Val
            }
            if curr.Left != nil {
                queue.PushBack(curr.Left)
            }
            if curr.Right != nil {
                queue.PushBack(curr.Right)
            }
        }
        res = append(res, levelNodes)
        fromRight = !fromRight
    }

    return res
}


func zigzagLevelOrder(root *TreeNode) [][]int {
    var res = make([][]int, 0)

    var preOrder func(*TreeNode,  int)
    preOrder = func(node *TreeNode, currLevel int) {
        if node == nil {
            return
        }
        if len(res) == currLevel {
            var levelNodes = make([]int, 0)
            res = append(res, levelNodes)
        }

        if currLevel % 2 == 0 {
            res[currLevel] = append(res[currLevel], node.Val)
        } else {
            res[currLevel] = append([]int{node.Val}, res[currLevel]...)
        }

        preOrder(node.Left, currLevel + 1)
        preOrder(node.Right, currLevel + 1)
    }

    preOrder(root, 0)

    return res
}