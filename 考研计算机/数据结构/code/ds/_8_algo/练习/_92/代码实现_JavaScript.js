/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
/**
 * @param {ListNode} head
 * @param {number} left
 * @param {number} right
 * @return {ListNode}
 */
var reverseBetween1 = function(head, left, right) {
    const dummyNode = new ListNode(-1)
    dummyNode.next = head

    let prev = dummyNode
    for (let i = 0; i < left - 1; i++) {
        prev = prev.next
    }
    const leftNode = prev.next

    let rightNode = leftNode
    for (let i = 0; i < right - left; i++) {
        rightNode = rightNode.next
    }
    const postRight = rightNode.next

    prev.next = null
    rightNode.next = null
    reverseList(leftNode)

    prev.next = rightNode
    leftNode.next = postRight

    return dummyNode.next
};

var reverseList = function(head) {
    let prev = null, curr = head
    while (curr) {
        const next = curr.next
        curr.next = prev
        prev = curr
        curr = next
    }
    return prev
};

// 头插法
var reverseBetween = function(head, left, right) {
    const dummyNode = new ListNode(-1)
    dummyNode.next = head

    let prev = dummyNode
    for (let i = 0; i < left - 1; i++) {
        prev = prev.next
    }

    let curr = prev.next
    for (let i = 0; i < right - left; i++) {
        const next = curr.next
        curr.next = next.next
        next.next = prev.next
        prev.next = next
    }

    return dummyNode.next
}