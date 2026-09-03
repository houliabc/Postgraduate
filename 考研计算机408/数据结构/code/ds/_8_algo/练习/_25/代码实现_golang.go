/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func reverseKGroup(head *ListNode, k int) *ListNode {
    if head == nil || head.Next == nil || k == 0 || k == 1 {
        return head
    }

    var dummyNode = &ListNode{Next:head}

    var prev, first, last = dummyNode, head, head
    for first != nil {
        for i := 0; i < k - 1; i++ {
            last = last.Next
            if last == nil {
                return dummyNode.Next
            }
        }
        var n = last.Next
        last.Next = nil

        reverseList(first)

        prev.Next, first.Next = last, n

        prev = first
        first = n
        last = first
    }

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