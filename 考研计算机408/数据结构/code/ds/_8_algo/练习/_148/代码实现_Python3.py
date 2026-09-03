# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    # 第一种解法：递归实现
    def sortList1(self, head: ListNode) -> ListNode:
        if not head or not head.next:
            return head

        slow, fast = head, head.next
        while fast and fast.next:
            slow, fast = slow.next, fast.next.next

        right_head = slow.next
        slow.next = None

        left, right = self.sortList1(head), self.sortList1(right_head)
        return self.mergeTwoLists(left, right)

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


    # 第二种解法：自底朝上实现归并排序第一种解法：递归实现
    def sortList(self, head: ListNode) -> ListNode:
        if not head or not head.next:
            return head

        dummy_node = ListNode(-1)
        dummy_node.next = head

        length = 0
        while head:
            length += 1
            head = head.next

        # bug 修复：step 从 1 开始，而不是从 0 开始
        step = 1
        while step < length:
            prev, curr = dummy_node, dummy_node.next
            while curr:
                left = curr
                right = self.split(left, step)
                # 分割得到下次处理的链表头
                curr = self.split(right, step)
                # 合并 left 和 right 链表
                prev = self.merge(left, right, prev)
            step <<= 1

        return dummy_node.next

    # 将 node 从第 step 个节点切断，并返回右边链表的头节点
    def split(self, node: ListNode, step: int) -> ListNode:
        if not node: return None
        for i in range(1, step):
            if node.next:
                node = node.next
        right = node.next
        node.next = None
        return right

    # 合并 left 和 right 两个有序链表
    # 将 prev.next 设置为合并之后链表的表头
    # 返回合并之后链表的最后一个节点
    def merge(self, left: ListNode, right: ListNode, prev: ListNode) -> ListNode:
        curr = prev
        while left and right:
            if left.val <= right.val:
                curr.next = left
                left = left.next
            else:
                curr.next = right
                right = right.next
            curr = curr.next
        if left: curr.next = left
        if right: curr.next = right
        # 保证 curr 是合并之后链表的最后一个节点
        # bug 修复：使用 while 循环找到最后一个节点
        while curr.next: curr = curr.next
        return curr