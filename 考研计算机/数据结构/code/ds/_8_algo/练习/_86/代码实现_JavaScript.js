/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
/**
 * @param {ListNode} head
 * @param {number} x
 * @return {ListNode}
 */
var partition = function(head, x) {
    if (!head || !head.next) return head

    const smallHead = new ListNode(-1), largeHead = new ListNode(-1)
    let small = smallHead, large = largeHead
    while (head) {
        if (head.val < x) {
            small.next = head
            small = small.next
        } else {
            large.next = head
            large = large.next
        }
        head = head.next
    }
    small.next = largeHead.next
    large.next = null
    return smallHead.next
};