/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
// 哈希辅助查找
func getIntersectionNode1(headA, headB *ListNode) *ListNode {
    if headA == nil || headB == nil {
        return nil
    }

    var set = make(map[*ListNode]bool)
    for headA != nil {
        set[headA] = true
        headA = headA.Next
    }

    for headB != nil {
        if set[headB] {
            return headB
        }
        headB = headB.Next
    }

    return nil
}

// 双指针
func getIntersectionNode(headA, headB *ListNode) *ListNode {
    if headA == nil || headB == nil {
        return nil
    }

    var a, b = headA, headB
    for a != b {
        if a == nil {
            a = headB
        } else {
            a = a.Next
        }

        if b == nil {
            b = headA
        } else {
            b = b.Next
        }
    }

    return a
}