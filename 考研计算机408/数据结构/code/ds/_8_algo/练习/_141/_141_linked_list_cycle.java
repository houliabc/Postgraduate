package com.douma._14_day_链表一._141;

import com.douma._14_day_链表一.ListNode;

import java.util.HashSet;
import java.util.Set;

/**
 * 高频算法面试题
 *      力扣 141 题：环形链表
 */
public class _141_linked_list_cycle {

    // 快慢指针
    // 时间复杂度：O(n):
    // 当链表中不存在环时，快指针将先于慢指针到达链表尾部，链表中每个节点至多被访问两次。
    // 当链表中存在环时，每一轮移动后，快慢指针的距离将减小一。而初始距离为环的长度，因此至多移动 NN 轮。
    // 空间复杂度：O(1)
    public boolean hasCycle(ListNode head) {
        ListNode slow = head;
        ListNode fast = head;
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
            if (slow == fast) return true;
        }
        return false;
    }

    /* 141. 环形链表
    给定一个链表，判断链表中是否有环。

    如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。

    为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。
    如果 pos 是 -1，则在该链表中没有环。
    注意：pos 不作为参数进行传递，仅仅是为了标识链表的实际情况。

    如果链表中存在环，则返回 true 。 否则，返回 false 。

    提示：
    链表中节点的数目范围是 [0, 10^4]
    -10^5 <= Node.val <= 10^5
    pos 为 -1 或者链表中的一个 有效索引 。

    进阶：
    你能用 O(1)（即，常量）内存解决此问题吗？
     */

    // 哈希查找
    // 时间复杂度：O(n)
    // 空间复杂度：O(n)
    public boolean hasCycle1(ListNode head) {
        Set<ListNode> set = new HashSet<>();
        while (head != null) {
            if (set.contains(head)) return true;
            set.add(head);
            head = head.next;
        }
        return false;
    }



}
