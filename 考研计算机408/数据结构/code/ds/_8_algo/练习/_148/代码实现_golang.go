/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
// 第一种解法：递归实现
func sortList1(head *ListNode) *ListNode {
    if head == nil || head.Next == nil {
        return head
    }

    // 找到中间节点
    var slow, fast = head, head.Next
    for fast != nil && fast.Next != nil {
        slow = slow.Next
        fast = fast.Next.Next
    }

    var rightHead = slow.Next
    slow.Next = nil

    var left = sortList1(head)
    var right = sortList1(rightHead)

    return mergeTwoLists(left, right)
}

func mergeTwoLists(l1 *ListNode, l2 *ListNode) *ListNode {
    if l1 == nil {
        return l2
    }
    if l2 == nil {
        return l1
    }

    var dummyNode = &ListNode{Val:-1}
    var curr = dummyNode

    for l1 != nil && l2 != nil {
        if l1.Val <= l2.Val {
            curr.Next = l1
            l1 = l1.Next
        } else {
            curr.Next = l2
            l2 = l2.Next
        }
        curr = curr.Next
    }

    if l1 == nil {
        curr.Next = l2
    }
    if l2 == nil {
        curr.Next = l1
    }

    return dummyNode.Next
}


// 第二种解法：自底朝上实现归并排序
func sortList(head *ListNode) *ListNode {
    if head == nil || head.Next == nil {
        return head
    }

    var dummy = &ListNode{Next:head}
    // 计算链表的长度
    var length = 0;
    for head != nil {
        length++
        head = head.Next
    }

    // bug 修复：step 从 1 开始，而不是从 0 开始
    for step := 1; step < length; step <<= 1 {
        var prev, curr = dummy, dummy.Next
        for curr != nil {
            var left = curr
            var right = split(left, step)
            // 分割得到下次处理的链表头
            curr = split(right, step)
            // 合并 left 和 right 链表
            prev = merge(left, right, prev)
        }
    }
    return dummy.Next
}

// 将 node 从第 step 个节点切断，并返回右边链表的头节点
func split(node *ListNode, step int) *ListNode {
    if node == nil {
        return nil
    }
    // 找到分割点
    for i := 1; node.Next != nil && i < step; i++ {
        node = node.Next
    }
    var right = node.Next
    node.Next = nil

    return right
}

// 合并 left 和 right 两个有序链表
// 将 prev.next 设置为合并之后链表的表头
// 返回合并之后链表的最后一个节点
func merge(left *ListNode, right *ListNode, prev *ListNode) *ListNode {
    var curr = prev
    for left != nil && right != nil {
        if left.Val <= right.Val {
            curr.Next = left
            left = left.Next
        } else {
            curr.Next = right
            right = right.Next
        }
        curr = curr.Next
    }
    if left == nil {
        curr.Next = right
    }
    if right == nil {
        curr.Next = left
    }
    // 保证 curr 是合并之后链表的最后一个节点
    // bug 修复：使用 while 循环找到最后一个节点
    for curr.Next != nil {
        curr = curr.Next
    }
    return curr
}