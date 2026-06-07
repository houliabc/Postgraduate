# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    # 堆和优先队列
    # 时间复杂度：O(k*n*logk)
    # 空间复杂度：O(logk)
    def mergeKLists(self, lists: List[ListNode]) -> ListNode:
        if len(lists) == 0: return None
        pq = []
        for i in range(len(lists)):
            if lists[i]:
                heapq.heappush(pq, (lists[i].val, i))
                lists[i] = lists[i].next

        dummy_node = ListNode(-1)
        curr = dummy_node
        while pq:
            val, idx = heapq.heappop(pq)
            curr.next = ListNode(val)
            curr = curr.next
            if lists[idx]:
                heapq.heappush(pq, (lists[idx].val, idx))
                lists[idx] = lists[idx].next
        return dummy_node.next

    # 分治思想
    # 时间复杂度：O(k*n*logk)
    # 空间复杂度：O(logk)
    def mergeKLists(self, lists: List[ListNode]) -> ListNode:
        if len(lists) == 0: return None
        return self.merge(lists, 0, len(lists) - 1)

    def merge(self, lists: List[ListNode], left: int, right: int) -> ListNode:
        if left == right: return lists[left]

        mid = left + (right - left) // 2
        merged_left_list = self.merge(lists, left, mid)
        merged_right_list = self.merge(lists, mid + 1, right)

        return self.mergeTwoLists(merged_left_list, merged_right_list)


    # 顺序合并
    # 时间复杂度：O(k^2 * n)
    # 空间复杂度：O(1)
    def mergeKLists1(self, lists):
        if len(lists) == 0: return None
        outputList = lists[0]
        for i in range(1, len(lists)):
            outputList = self.mergeTwoLists(outputList, lists[i])
        return outputList

    def mergeTwoLists(self, l1: ListNode, l2: ListNode) -> ListNode:
        if not l1: return l2
        if not l2: return l1

        dummy_node = ListNode(-1)
        curr = dummy_node
        while l1 and l2:
            if l1.val <= l2.val:
                curr.next = l1
                l1 = l1.next
            else:
                curr.next = l2
                l2 = l2.next
            curr = curr.next

        if l1: curr.next = l1
        if l2: curr.next = l2

        return dummy_node.next