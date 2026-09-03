/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func partition(head *ListNode, x int) *ListNode {
    if head == nil || head.Next == nil {
        return head
    }

    var smallHead, largeHead = &ListNode{Val:-1}, &ListNode{Val:-1}
    var small, large = smallHead, largeHead

    for head != nil {
        if head.Val < x {
            small.Next = head
            small = small.Next
        } else {
            large.Next = head
            large = large.Next
        }
        head = head.Next
    }

    large.Next = nil
    small.Next = largeHead.Next
    return smallHead.Next
}