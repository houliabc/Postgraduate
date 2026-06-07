/**
 * Definition for singly-linked list.
 * function ListNode(val) {
 *     this.val = val;
 *     this.next = null;
 * }
 */

/**
 * @param {ListNode} headA
 * @param {ListNode} headB
 * @return {ListNode}
 */
var getIntersectionNode1 = function(headA, headB) {
    if (!headA || !headB) return null

    const visited = new Set()
    while (headA) {
        visited.add(headA)
        headA = headA.next
    }

    while (headB) {
        if (visited.has(headB)) return headB
        headB = headB.next
    }

    return null
};

var getIntersectionNode = function(headA, headB) {
    if (!headA || !headB) return null
    let a = headA, b = headB
    while (a != b) {
        a = (a == null) ? headB : a.next
        b = (b == null) ? headA : b.next
    }
    return a
}