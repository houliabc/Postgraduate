/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
/**
 * @param {ListNode} head
 * @return {ListNode}
 */
// 第一种解法：递归实现
var sortList1 = function(head) {
    if (!head || !head.next) return head

    let slow = head, fast = head.next
    while (fast && fast.next) {
        slow = slow.next
        fast = fast.next.next
    }

    const rightHead = slow.next
    slow.next = null

    const left = sortList1(head)
    const right = sortList1(rightHead)

    return mergeTwoLists(left, right)
};

var mergeTwoLists = function(l1, l2) {
    if (!l1) return l2
    if (!l2) return l1

    const dummyNode = new ListNode(-1)
    let curr = dummyNode;
    while (l1 && l2) {
        if (l1.val <= l2.val) {
            curr.next = l1
            l1 = l1.next
        } else {
            curr.next = l2
            l2 = l2.next
        }
        curr = curr.next
    }
    if (l1) curr.next = l1
    if (l2) curr.next = l2
    return dummyNode.next
};


// 第二种解法：自底朝上实现归并排序
var sortList = function(head) {
    if (!head || !head.next) return head

    const dummyNode = new ListNode(-1)
    dummyNode.next = head

    let length = 0
    while (head) {
        length++
        head = head.next
    }

    // bug 修复：step 从 1 开始，而不是从 0 开始
    for (let step = 1; step < length; step <<= 1) {
        let prev = dummyNode, curr = dummyNode.next
        while (curr) {
            const left = curr
            const right = split(left, step)
            // 分割得到下次处理的链表头
            curr = split(right, step)
            // 合并 left 和 right 链表
            prev = merge(left, right, prev)
        }
    }

    return dummyNode.next
}

// 将 node 从第 step 个节点切断，并返回右边链表的头节点
var split = function(node, step) {
    if (!node) return null
    for (let i = 1; node.next && i < step; i++) {
        node = node.next
    }
    const right = node.next
    node.next = null
    return right
}

// 合并 left 和 right 两个有序链表
    // 将 prev.next 设置为合并之后链表的表头
    // 返回合并之后链表的最后一个节点
var merge = function(left, right, prev) {
    let curr = prev
    while (left && right) {
        if (left.val <= right.val) {
            curr.next = left
            left = left.next
        } else {
            curr.next = right
            right = right.next
        }
        curr = curr.next
    }
    if (left) curr.next = left
    if (right) curr.next = right
    // 保证 curr 是合并之后链表的最后一个节点
    // bug 修复：使用 while 循环找到最后一个节点
    while (curr.next) curr = curr.next
    return curr
}

