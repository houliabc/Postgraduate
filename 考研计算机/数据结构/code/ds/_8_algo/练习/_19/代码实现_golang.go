/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func removeNthFromEnd1(head *ListNode, n int) *ListNode {
    if head == nil {
        return head
    }

    var dummyNode = &ListNode{Next:head}

    // 1. 计算链表的长度
    var length, curr = 0, dummyNode
    for curr != nil {
        length++
        curr = curr.Next
    }

    // 2. 找到倒数第 n 个节点的前一个节点
    var prev = dummyNode
    for i := 1; i < length - n; i++ {
        prev = prev.Next
    }

    // 3. 删除倒数第 n 个节点
    var delNode = prev.Next
    prev.Next = delNode.Next
    delNode.Next = nil

    return dummyNode.Next
}

// 快慢指针
func removeNthFromEnd(head *ListNode, n int) *ListNode {
    if head == nil {
        return head
    }

    var dummyNode = &ListNode{Next:head}
    var slow, fast = dummyNode, dummyNode

    // fast 先走 n + 1
    for n >= 0 {
        fast = fast.Next
        n--
    }

    for fast != nil {
        slow = slow.Next
        fast = fast.Next
    }

    var delNode = slow.Next
    slow.Next = delNode.Next
    delNode.Next = nil

    return dummyNode.Next
}