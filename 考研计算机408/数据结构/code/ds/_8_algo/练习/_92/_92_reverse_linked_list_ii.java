package com.douma._14_day_链表一._92;

import com.douma._14_day_链表一.ListNode;

/**
 * @官方网站 : https://douma.ke.qq.com
 * @微信公众号 : 抖码课堂
 * @官方微信号 : bigdatatang01
 * 抖码算法，让算法学习变的简单有趣
 * @作者 : 老汤
 */
public class _92_reverse_linked_list_ii {
    /* 92. 反转链表 II
    给你单链表的头指针 head 和两个整数 left 和 right ，其中 left <= right 。
    请你反转从位置 left 到位置 right 的链表节点，返回 反转后的链表 。

    输入：head = 1->2->3->4->5, left = 2, right = 4
    输出： 1->4->3->2->5

    提示：
        链表中节点数目为 n
        1 <= n <= 500
        -500 <= Node.val <= 500
        1 <= left <= right <= n

    进阶： 你可以使用一趟扫描完成反转吗？
     */

    public ListNode reverseBetween1(ListNode head, int left, int right) {
        // 因为有头节点也可能变化，所以为了统一逻辑，这里设置虚拟节点
        ListNode dummyNode = new ListNode(-1);
        dummyNode.next = head;

        // 1. 从虚拟节点走 left - 1 步，来到 left 节点的前一个节点
        ListNode prev = dummyNode;
        for (int i = 0; i < left - 1; i++) {
            prev = prev.next;
        }
        ListNode leftNode = prev.next;

        // 2. 从 leftNode 节点开始走 right - left 步，来到 right 节点
        ListNode rightNode = leftNode;
        for (int i = 0; i < right - left; i++) {
            rightNode = rightNode.next;
        }
        ListNode postRight = rightNode.next;

        // 3. 切断得到 left 到 right 的子链表
        prev.next = null;
        rightNode.next = null;

        // 4. 反转 leftNode 到 rightNode
        reverseList(leftNode);

        // 5. 将反转后的子链表接回到原链表
        prev.next = rightNode;
        leftNode.next = postRight;

        return dummyNode.next;
    }

    // 迭代
    private void reverseList(ListNode head) {
        ListNode prev = null;
        ListNode curr = head;
        while (curr != null) {
            ListNode next = curr.next;
            curr.next = prev;
            prev = curr;
            curr = next;
        }
    }

    // 头插法
    public ListNode reverseBetween(ListNode head, int left, int right) {
        // 因为有头节点也可能变化，所以为了统一逻辑，这里设置虚拟节点
        ListNode dummyNode = new ListNode(-1);
        dummyNode.next = head;

        ListNode prev = dummyNode;
        for (int i = 0; i < left - 1; i++) {
            prev = prev.next;
        }

        ListNode curr = prev.next;
        for (int i = 0; i < right - left; i++) {
            ListNode next = curr.next;
            curr.next = next.next;
            next.next = prev.next;
            prev.next = next;
        }

        return dummyNode.next;
    }
}
