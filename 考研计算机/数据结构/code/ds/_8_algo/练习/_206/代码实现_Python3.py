# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def reverseList(self, head: ListNode) -> ListNode:
        if head is None or head.next is None:
            return head

        p = self.reverseList(head.next)
        head.next.next = head
        head.next = None

        return p

    def reverseList1(self, head: ListNode) -> ListNode:
        prev, curr = None, head
        while curr is not None:
            next = curr.next
            curr.next = prev
            prev = curr
            curr = next
        return prev