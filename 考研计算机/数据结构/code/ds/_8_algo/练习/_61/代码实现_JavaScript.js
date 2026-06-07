/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
/**
 * @param {ListNode} head
 * @param {number} k
 * @return {ListNode}
 */
var rotateRight = function(head, k) {
    if (!head || !head.next || k == 0) return head

    let len = 1, lastNode = head
    while (lastNode.next) {
        len++
        lastNode = lastNode.next
    }

    if (k % len == 0) return head
    k = k % len

    let newTail = head
    for (let i = 0; i < len - k - 1; i++) {
        newTail = newTail.next;
    }

    const newHead = newTail.next;
    newTail.next = null
    lastNode.next = head

    return newHead
};