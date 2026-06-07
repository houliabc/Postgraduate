package com.douma._15_day_链表二._86;

import com.douma._15_day_链表二.ListNode;

/**
 * @官方网站 : https://douma.ke.qq.com
 * @微信公众号 : 抖码课堂
 * @官方微信号 : bigdatatang01
 * 抖码算法，让算法学习变的简单有趣
 * @作者 : 老汤
 */
public class _86_partition_list {
    /* 86. 分隔链表
    给你一个链表的头节点 head 和一个特定值 x ，请你对链表进行分隔，
    使得所有 小于 x 的节点都出现在 大于或等于 x 的节点之前。

    你应当 保留 两个分区中每个节点的初始相对位置。

    输入：head = 1->4->3->2->5->2->NULL, x = 3
    输出：1->2->2->4->3->5->NULL
     */
    public ListNode partition(ListNode head, int x) {
        if (head == null || head.next == null) return head;

        ListNode smallHead = new ListNode(-1);
        ListNode small = smallHead;
        ListNode largeHead = new ListNode(-1);
        ListNode large = largeHead;

        while (head != null) {
            if (head.val < x) {
                small.next = head;
                small = small.next;
            } else {
                large.next = head;
                large = large.next;
            }
            head = head.next;
        }

        large.next = null;
        small.next = largeHead.next;

        return smallHead.next;
    }

}
