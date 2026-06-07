# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def reverseBetween1(self, head: ListNode, left: int, right: int) -> ListNode:
        dummy_node = ListNode(-1)
        dummy_node.next = head

        prev = dummy_node
        for i in range(0, left - 1):
            prev = prev.next
        left_node = prev.next

        right_node = left_node
        for i in range(0, right - left):
            right_node = right_node.next
        post_right = right_node.next

        prev.next = None
        right_node.next = None

        self.reverseList(left_node)

        prev.next = right_node
        left_node.next = post_right

        return dummy_node.next

    def reverseList(self, head: ListNode) -> ListNode:
        prev, curr = None, head
        while curr is not None:
            next = curr.next
            curr.next = prev
            prev = curr
            curr = next
        return prev

    # 头插法
    def reverseBetween(self, head: ListNode, left: int, right: int) -> ListNode:
        dummy_node = ListNode(-1)
        dummy_node.next = head

        prev = dummy_node
        for i in range(0, left - 1):
            prev = prev.next

        curr = prev.next
        for i in range(0, right - left):
            next = curr.next
            curr.next = next.next
            next.next = prev.next
            prev.next = next

        return dummy_node.next