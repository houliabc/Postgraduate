/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
// DFS
func isSameTree1(p *TreeNode, q *TreeNode) bool {
    if p == nil && q == nil {
        return true
    } else if p == nil || q == nil {
        return false
    } else if p.Val != q.Val {
        return false
    }

    return isSameTree1(p.Left, q.Left) && isSameTree1(p.Right, q.Right)
}


// BFS
func isSameTree(p *TreeNode, q *TreeNode) bool {
    if p == nil && q == nil {
        return true
    } else if p == nil || q == nil {
        return false
    }

    var queue1, queue2 = list.New(), list.New()
    queue1.PushBack(p)
    queue2.PushBack(q)
    for queue1.Len() > 0 && queue2.Len() > 0 {
        var node1 = queue1.Remove(queue1.Front()).(*TreeNode)
        var node2 = queue2.Remove(queue2.Front()).(*TreeNode)
        if node1.Val != node2.Val {
            return false
        }
        var left1, right1 = node1.Left, node1.Right
        var left2, right2 = node2.Left, node2.Right
        if (left1 == nil) != (left2 == nil) {
            return false
        }
        if (right1 == nil) != (right2 == nil) {
            return false
        }
        if left1 != nil {
            queue1.PushBack(left1)
        }
        if right1 != nil {
            queue1.PushBack(right1)
        }
        if left2 != nil {
            queue2.PushBack(left2)
        }
        if right2 != nil {
            queue2.PushBack(right2)
        }
    }
    return queue1.Len() == 0 && queue2.Len() == 0
}