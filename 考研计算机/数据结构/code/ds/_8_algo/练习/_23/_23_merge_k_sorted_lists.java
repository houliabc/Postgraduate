package com.douma._15_day_链表二._23;

import com.douma._15_day_链表二.ListNode;

import java.util.PriorityQueue;

/**
 * @官方网站 : https://douma.ke.qq.com
 * @微信公众号 : 抖码课堂
 * @官方微信号 : bigdatatang01
 * 抖码算法，让算法学习变的简单有趣
 * @作者 : 老汤
 */
public class _23_merge_k_sorted_lists {
    // 优先队列
    // 时间复杂度：O(k*n*logk)
    // 空间复杂度：O(k)
    public ListNode mergeKLists1(ListNode[] lists) {
        // 小顶堆
        PriorityQueue<ListNode> pq
                = new PriorityQueue<>((o1, o2) -> o1.val - o2.val);

        // O(k*logk)
        for (ListNode node : lists) { // O(k)
            // bug 修复：防止链表为空
            if (node == null) continue;
            pq.add(node); // O(logk)
        }

        ListNode dummyNode = new ListNode(-1);
        ListNode curr = dummyNode;
        // O(kn*logk)
        while (!pq.isEmpty()) { // O(kn)
            ListNode minNode = pq.remove(); // O(logk)
            curr.next = minNode;
            curr = curr.next;

            if (minNode.next != null) {
                pq.add(minNode.next); // O(logk)
            }
        }
        return dummyNode.next;
    }

    // 顺序合并
    // 时间复杂度：O(k^2 * n)
    // 空间复杂度：O(1)
    public ListNode mergeKLists2(ListNode[] lists) {
        if (lists == null || lists.length == 0)
            return null;
        ListNode outputList = lists[0];
        for (int i = 1; i < lists.length; i++) {
            outputList = mergeTwoLists(outputList, lists[i]);
        }
        return outputList;
    }

    // 分治思想
    // 时间复杂度：O(k*n*logk)
    // 空间复杂度：O(logk)
    public ListNode mergeKLists3(ListNode[] lists) {
        if (lists == null || lists.length == 0)
            return null;
        return merge(lists, 0, lists.length - 1);
    }

    private ListNode merge(ListNode[] lists, int left, int right) {
        if (left == right) return lists[left];

        int mid = left + (right - left) / 2;

        ListNode mergedLeftList = merge(lists, left, mid);
        ListNode mergedRightList = merge(lists, mid + 1, right);

        return mergeTwoLists(mergedLeftList, mergedRightList);
    }

    // 时间复杂度：O(2n)
    // 空间复杂度：O(1)
    public ListNode mergeTwoLists(ListNode l1, ListNode l2) {
        if (l1 == null) return l2;
        if (l2 == null) return l1;

        ListNode dummyNode = new ListNode(-1);
        ListNode curr = dummyNode;

        while (l1 != null && l2 != null) {
            if (l1.val <= l2.val) {
                curr.next = l1;
                l1 = l1.next;
            } else {
                curr.next = l2;
                l2 = l2.next;
            }
            curr = curr.next;
        }

        if (l1 == null) curr.next = l2;
        if (l2 == null) curr.next = l1;

        return dummyNode.next;
    }
}
