# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def isPalindrome(self, head: ListNode) -> bool:
        if not head or not head.next:
            return True

        slow, fast = head, head.next
        while fast and fast.next:
            slow, fast = slow.next, fast.next.next

        new_head = slow.next
        slow.next = None

        left, right = head, self.reverseList(new_head)
        while right:
            if left.val != right.val: return False
            left, right = left.next, right.next

        return True

    def reverseList(self, head: ListNode) -> ListNode:
        prev, curr = None, head
        while curr:
            next = curr.next
            curr.next = prev
            prev = curr
            curr = next
        return prev