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
var reverseKGroup = function(head, k) {
    if (!head || !head.next || k == 0 || k == 1) {
        return head
    }

    const dummyNode = new ListNode(-1)
    dummyNode.next = head

    let prev = dummyNode, first = head, last = head
    while (first) {
        for (let i = 0; i < k - 1; i++) {
            last = last.next
            if (!last) return dummyNode.next
        }
        const next = last.next
        last.next = null

        reverse(first)

        prev.next = last
        first.next = next

        prev = first
        first = next
        last = first
    }
    return dummyNode.next
};

var reverse = function(head) {
    let prev = null, curr = head
    while (curr) {
        const next = curr.next
        curr.next = prev
        prev = curr
        curr = next
    }
    return prev
};