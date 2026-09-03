# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def reverseKGroup(self, head: ListNode, k: int) -> ListNode:
        if not head or not head.next or k == 0 or k == 1:
            return head

        dummy_node = ListNode(-1)
        dummy_node.next = head

        prev, first, last = dummy_node, head, head
        while first:
            for i in range(k - 1):
                last = last.next
                if not last: return dummy_node.next
            next = last.next
            last.next = None
            self.reverse(first)

            prev.next = last
            first.next = next

            prev = first
            first = next
            last = first

        return dummy_node.next

    def reverse(self, head: ListNode) -> ListNode:
        prev, curr = None, head
        while curr is not None:
            next = curr.next
            curr.next = prev
            prev = curr
            curr = next
        return prev