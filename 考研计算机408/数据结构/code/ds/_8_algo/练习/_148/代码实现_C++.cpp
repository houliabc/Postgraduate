/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    // 第一种解法：递归实现
    ListNode* sortList1(ListNode* head) {
        if (!head || !head->next) return head;
        // 找到中间节点
        ListNode *slow = head, *fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode *rightHead = slow->next;
        slow->next = nullptr;

        ListNode *left = sortList1(head);
        ListNode *right = sortList1(rightHead);

        return mergeTwoLists(left, right);
    }

    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr) return l2;
        if (l2 == nullptr) return l1;

        ListNode* dummyNode = new ListNode(-1);
        ListNode *curr = dummyNode;

        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val <= l2->val) {
                curr->next = l1;
                l1 = l1->next;
            } else {
                curr->next = l2;
                l2 = l2->next;
            }
            curr = curr->next;
        }

        if (l1 == nullptr) curr->next = l2;
        if (l2 == nullptr) curr->next = l1;

        return dummyNode->next;
    }

    // 第二种解法：自底朝上实现归并排序
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;

        ListNode* dummyNode = new ListNode(-1);
        dummyNode->next = head;

        // 计算链表的长度
        int length = 0;
        while (head) {
            length++;
            head = head->next;
        }

        // bug 修复：step 从 1 开始，而不是从 0 开始
        for (int step = 1; step < length; step <<= 1) {
            ListNode *prev = dummyNode;
            ListNode *curr = dummyNode->next;
            while (curr) {
                ListNode *left = curr;
                ListNode *right = split(left, step);
                // 分割得到下次处理的链表头
                curr = split(right, step);
                // 合并 left 和 right 链表
                prev = merge(left, right, prev);
            }
        }

        return dummyNode->next;
    }

    // 将 node 从第 step 个节点切断，并返回右边链表的头节点
    ListNode* split(ListNode* node, int step) {
        if (!node) return nullptr;
        // 找到分割点
        for (int i = 1; node->next && i < step; i++) {
            node = node->next;
        }
        ListNode *right = node->next;
        node->next = nullptr;
        return right;
    }

    // 合并 left 和 right 两个有序链表
    // 将 prev.next 设置为合并之后链表的表头
    // 返回合并之后链表的最后一个节点
    ListNode* merge(ListNode* left, ListNode* right, ListNode* prev) {
        ListNode *curr = prev;
        while (left && right) {
            if (left->val <= right->val) {
                curr->next = left;
                left = left->next;
            } else {
                curr->next = right;
                right = right->next;
            }
            curr = curr->next;
        }
        if (left) curr->next = left;
        if (right) curr->next = right;
        // 保证 curr 是合并之后链表的最后一个节点
        // bug 修复：使用 while 循环找到最后一个节点
        while (curr->next) curr = curr->next;
        return curr;
    }
};