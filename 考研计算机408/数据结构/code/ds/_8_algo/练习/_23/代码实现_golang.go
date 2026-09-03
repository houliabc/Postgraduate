/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */

type minHeap []*ListNode

func (h minHeap) Len() int           { return len(h) }
func (h minHeap) Less(i, j int) bool { return h[i].Val < h[j].Val }
func (h minHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }
func (h *minHeap) Push(x interface{}) {
	// Push and Pop use pointer receivers because they modify the slice's length,
	// not just its contents.
	*h = append(*h, x.(*ListNode))
}
func (h *minHeap) Pop() interface{} {
	old := *h
	n := len(old)
	x := old[n-1]
	*h = old[0 : n-1]
	return x
}

// 优先队列
// 时间复杂度：O(k*n*logk)
// 空间复杂度：O(k)
func mergeKLists1(lists []*ListNode) *ListNode {
    var pq = &minHeap{}

    for _, node := range lists {
        // bug 修复：防止链表为空
        if node == nil {
            continue
        }
        heap.Push(pq, node)
    }

    var dummyNode = &ListNode{Val:-1}
    var curr = dummyNode
    for pq.Len() > 0 {
        var minNode = heap.Pop(pq).(*ListNode)
        curr.Next = minNode
        curr = curr.Next

        if minNode.Next != nil {
            heap.Push(pq, minNode.Next)
        }
    }

    return dummyNode.Next
}

// 顺序合并
// 时间复杂度：O(k^2 * n)
// 空间复杂度：O(1)
func mergeKLists2(lists []*ListNode) *ListNode {
    if lists == nil || len(lists) == 0 {
        return nil
    }
    var outputList = lists[0]
    for i := 1; i < len(lists); i++ {
        outputList = mergeTwoLists(outputList, lists[i])
    }
    return outputList
}


// 分治思想
// 时间复杂度：O(k*n*logk)
// 空间复杂度：O(logk)
func mergeKLists(lists []*ListNode) *ListNode {
    if lists == nil || len(lists) == 0 {
        return nil
    }
    return merge(lists, 0, len(lists) - 1)
}

func merge(lists []*ListNode, left int, right int) *ListNode {
    if left == right {
        return lists[left]
    }

    var mid = left + (right - left) / 2

    var mergedLeftList = merge(lists, left, mid)
    var mergedRightList = merge(lists, mid + 1, right)

    return mergeTwoLists(mergedLeftList, mergedRightList)
}

func mergeTwoLists(l1 *ListNode, l2 *ListNode) *ListNode {
    if l1 == nil {
        return l2
    }
    if l2 == nil {
        return l1
    }

    var dummyNode = &ListNode{Val:-1}
    var curr = dummyNode

    for l1 != nil && l2 != nil {
        if l1.Val <= l2.Val {
            curr.Next = l1
            l1 = l1.Next
        } else {
            curr.Next = l2
            l2 = l2.Next
        }
        curr = curr.Next
    }

    if l1 == nil {
        curr.Next = l2
    }
    if l2 == nil {
        curr.Next = l1
    }

    return dummyNode.Next
}

