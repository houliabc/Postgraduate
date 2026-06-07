# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def getIntersectionNode1(self, headA: ListNode, headB: ListNode) -> ListNode:
        if not headA or not headB:
            return None

        visited = set()
        while headA:
            visited.add(headA)
            headA = headA.next

        while headB:
            if headB in visited:
                return headB
            headB = headB.next

        return None

    def getIntersectionNode(self, headA: ListNode, headB: ListNode) -> ListNode:
        if not headA or not headB:
            return None
        a, b = headA, headB
        while a != b:
            a = headB if a == None else a.next
            b = headA if b == None else b.next
        return a