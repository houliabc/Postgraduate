/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
/**
 * @param {ListNode} head
 * @return {boolean}
 */
var isPalindrome = function(head) {
    if (!head || !head.next) return true

    let slow = head, fast = head.next
    while (fast && fast.next) {
        slow = slow.next
        fast = fast.next.next
    }

    const newHead = slow.next
    slow.next = null

    let left = head, right = reverseList(newHead)
    while (right) {
        if (left.val != right.val) return false
        left = left.next
        right = right.next
    }
    return true
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