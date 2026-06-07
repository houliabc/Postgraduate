/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
/**
 * @param {ListNode[]} lists
 * @return {ListNode}
 */
// 分治思想
// 时间复杂度：O(k*n*logk)
// 空间复杂度：O(logk)
const mergeKLists = function(lists) {
        if (lists.length == 0) return null
        return merge(lists, 0, lists.length - 1)
    };

const merge = function(lists, left, right) {
    if (left == right) return lists[left]

    const mid = left + Math.floor((right - left) / 2)
    const mergedLeftList = merge(lists, left, mid)
    const mergedRightList = merge(lists, mid + 1, right)

    return mergeTwoLists(mergedLeftList, mergedRightList)
}

// 顺序合并
// 时间复杂度：O(k^2 * n)
// 空间复杂度：O(1)
const mergeKLists1 = function (lists) {
    if (lists == null || lists.length == 0)
        return null
    let outputList = lists[0];
    for (let i = 1; i < lists.length; i++) {
        outputList = mergeTwoLists(outputList, lists[i]);
    }
    return outputList;
}

const mergeTwoLists = function(l1, l2) {
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

// 优先队列
// 时间复杂度：O(k*n*logk)
// 空间复杂度：O(k)
var mergeKLists = function(lists) {
    if (lists.length == 0) return null
    const pq = new MinPriorityQueue({priority: (node) => node.val})

    for (const node of lists) {
        if (node == null) continue
        pq.enqueue(node)
    }

    const dummyNode = new ListNode()
    let curr = dummyNode
    while (pq.size() > 0) {
        const minNode = pq.dequeue()["element"]
        curr.next = minNode
        curr = curr.next
        if (minNode.next) {
            pq.enqueue(minNode.next)
        }
    }

    return dummyNode.next
};