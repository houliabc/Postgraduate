/**
 * Definition for singly-linked list.
 * function ListNode(val) {
 *     this.val = val;
 *     this.next = null;
 * }
 */

/**
 * @param {ListNode} head
 * @return {boolean}
 */
var hasCycle1 = function(head) {
    const visited = new Set()
    while (head) {
        if (visited.has(head)) return true
        visited.add(head)
        head = head.next
    }
    return false
};

var hasCycle = function(head) {
    let slow = head, fast = head
    while (fast && fast.next) {
        slow = slow.next
        fast = fast.next.next
        if (slow == fast) return true
    }
    return false
}