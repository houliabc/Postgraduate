/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
// 两趟扫描
func reverseBetween1(head *ListNode, left int, right int) *ListNode {
    // 因为有头节点也可能变化，所以为了统一逻辑，这里设置虚拟节点
    var dummyNode = &ListNode{Next:head}

    // 1. 从虚拟节点走 left - 1 步，来到 left 节点的前一个节点
    var prev = dummyNode
    for i := 0; i < left - 1; i++ {
        prev = prev.Next
    }
    var leftNode = prev.Next

    // 2. 从 leftNode 节点开始走 right - left 步，来到 right 节点
    var rightNode = leftNode
    for i := 0; i < right - left; i++ {
        rightNode = rightNode.Next
    }
    var postRight = rightNode.Next

    // 3. 切断得到 left 到 right 的子链表
    prev.Next = nil
    rightNode.Next = nil

    // 4. 反转 leftNode 到 rightNode
    reverseList(leftNode)

    // 5. 将反转后的子链表接回到原链表
    prev.Next = rightNode
    leftNode.Next = postRight

    return dummyNode.Next
}

func reverseList(head *ListNode) *ListNode {
    var prev *ListNode = nil
    var curr = head
    for curr != nil {
        var next = curr.Next
        curr.Next = prev
        prev = curr
        curr = next
    }
    return prev
}

// 头插法
// 一遍扫描
func reverseBetween(head *ListNode, left int, right int) *ListNode {
    // 因为有头节点也可能变化，所以为了统一逻辑，这里设置虚拟节点
    var dummyNode = &ListNode{Next:head}

    var prev = dummyNode
    for i := 0; i < left - 1; i++ {
        prev = prev.Next
    }

    var curr = prev.Next
    for i := 0; i < right - left; i++ {
        var n = curr.Next
        curr.Next = n.Next
        n.Next = prev.Next
        prev.Next = n
    }

    return dummyNode.Next
}