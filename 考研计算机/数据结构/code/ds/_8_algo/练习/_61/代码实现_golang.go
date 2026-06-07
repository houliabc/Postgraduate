/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */

// 反转解法
func rotateRight1(head *ListNode, k int) *ListNode {
    if head == nil || head.Next == nil || k == 0 {
        return head
    }

    // 计算链表的长度
    var length, curr = 0, head
    for curr != nil {
        length++
        curr = curr.Next
    }

    if k % length == 0 {
        return head
    }
    k = k % length

    var newHead = reverseList(head)
    var kthNode = newHead
    for i := 0; i < k - 1; i++ {
        kthNode = kthNode.Next
    }

    var nextHead = kthNode.Next
    kthNode.Next = nil

    var retHead = reverseList(newHead)
    newHead.Next = reverseList(nextHead)

    return retHead
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

// 方法二
func rotateRight(head *ListNode, k int) *ListNode {
    if head == nil || head.Next == nil || k == 0 {
        return head
    }

    // 计算链表的长度
    var length, lastNode = 1, head
    for lastNode.Next != nil {
        length++
        lastNode = lastNode.Next
    }

    if k % length == 0 {
        return head
    }
    k = k % length

    var newTail = head
    for i := 0; i < length - k - 1; i++ {
        newTail = newTail.Next
    }

    var newHead = newTail.Next
    newTail.Next = nil
    lastNode.Next = head

    return newHead
}