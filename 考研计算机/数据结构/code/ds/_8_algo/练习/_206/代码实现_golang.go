/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
// 迭代
func reverseList1(head *ListNode) *ListNode {
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

// 递归
func reverseList(head *ListNode) *ListNode {
    if head == nil || head.Next == nil {
        return head
    }
    var p = reverseList(head.Next)
    head.Next.Next = head
    head.Next = nil
    return p
}