/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
/**
 * @param {ListNode} l1
 * @param {ListNode} l2
 * @return {ListNode}
 */
// 迭代解法
var mergeTwoLists1 = function(l1, l2) {
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

// 递归解法
var mergeTwoLists = function(l1, l2) {
    if (!l1) return l2
    if (!l2) return l1

    if (l1.val <= l2.val) {
        l1.next = mergeTwoLists(l1.next, l2)
        return l1
    } else {
        l2.next = mergeTwoLists(l1, l2.next)
        return l2
    }
};