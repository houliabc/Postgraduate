# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def rotateRight(self, head: ListNode, k: int) -> ListNode:
        if not head or not head.next or k == 0:
            return head

        length, last_node = 1, head
        while last_node.next:
            length, last_node = length + 1, last_node.next

        if k % length == 0: return head
        k = k % length

        new_tail = head
        for i in range(0, length - k - 1):
            new_tail = new_tail.next

        new_head = new_tail.next
        new_tail.next = None
        last_node.next = head

        return new_head