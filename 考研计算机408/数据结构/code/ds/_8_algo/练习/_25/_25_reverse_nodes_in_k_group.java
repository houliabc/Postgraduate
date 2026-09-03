package com.douma._14_day_链表一._25;

import com.douma._14_day_链表一.ListNode;

/**
 * @官方网站 : https://douma.ke.qq.com
 * @微信公众号 : 抖码课堂
 * @官方微信号 : bigdatatang01
 * 抖码算法，让算法学习变的简单有趣
 * @作者 : 老汤
 */
public class _25_reverse_nodes_in_k_group {
    /* 25. K 个一组翻转链表
    给你一个链表，每 k 个节点一组进行翻转，请你返回翻转后的链表。
    k 是一个正整数，它的值小于或等于链表的长度。
    如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。

    输入：1->2->3->4->5    k=2
    输出：2->1->4->3->5

    输入：1->2->3->4->5->6->7->8    k=3
    输出：3->2->1->6->5->4->7->8

    进阶：
    你可以设计一个只使用常数额外空间的算法来解决此问题吗？
    你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。

     */

    public ListNode reverseKGroup(ListNode head, int k) {
        if (head == null || head.next == null || k == 0 || k == 1) return head;

        ListNode dummyNode = new ListNode(-1);
        dummyNode.next = head;

        ListNode prev = dummyNode;
        ListNode first = head;
        ListNode last = first;
        while (first != null) {
            for (int i = 0; i < k - 1; i++) {
                last = last.next;
                if (last == null) return dummyNode.next;
            }
            ListNode next = last.next;
            last.next = null;

            reverse(first);

            prev.next = last;
            first.next = next;

            prev = first;
            first = next;
            last = first;
        }
        return dummyNode.next;
    }

    private ListNode reverse(ListNode head) {
        ListNode pre = null;
        ListNode curr = head;
        while (curr != null) {
            ListNode next = curr.next;
            curr.next = pre;

            pre = curr;
            curr = next;
        }
        return pre;
    }
}
