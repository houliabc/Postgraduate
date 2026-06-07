/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
// 哈希查找
// 时间复杂度：O(n)
// 空间复杂度：O(n)
func hasCycle1(head *ListNode) bool {
    var set = make(map[*ListNode]bool)
    for head != nil {
        if set[head] {
            return true
        }
        set[head] = true
        head = head.Next
    }
    return false
}

// 快慢指针
// 时间复杂度：O(n):
    // 当链表中不存在环时，快指针将先于慢指针到达链表尾部，链表中每个节点至多被访问两次。
    // 当链表中存在环时，每一轮移动后，快慢指针的距离将减小一。而初始距离为环的长度，因此至多移动 NN 轮。
// 空间复杂度：O(1)
func hasCycle(head *ListNode) bool {
    var slow, fast = head, head
    for fast != nil && fast.Next != nil {
        slow = slow.Next
        fast = fast.Next.Next
        if slow == fast {
            return true
        }
    }
    return false
}