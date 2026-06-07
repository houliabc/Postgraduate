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
    ListNode* reverseBetween1(ListNode* head, int left, int right) {
        ListNode* dummyNode = new ListNode(-1);
        dummyNode->next = head;

        // 1. 从虚拟节点走 left - 1 步，来到 left 节点的前一个节点
        ListNode *prev = dummyNode;
        for (int i = 0; i < left - 1; i++) {
            prev = prev->next;
        }
        ListNode *leftNode = prev->next;

        // 从 leftNode 节点开始走 right - left 步，来到 right 节点
        ListNode *rightNode = leftNode;
        for (int i = 0; i < right - left; i++) {
            rightNode = rightNode->next;
        }
        ListNode *postRight = rightNode->next;

        // 3. 切断得到 left 到 right 的子链表
        prev->next = nullptr;
        rightNode->next = nullptr;

        // 4. 反转 leftNode 到 rightNode
        reverseList(leftNode);

        // 5. 将反转后的子链表接回到原链表
        prev->next = rightNode;
        leftNode->next = postRight;

        return dummyNode->next;
    }

    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }

    // 头插法
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode* dummyNode = new ListNode(-1);
        dummyNode->next = head;

        ListNode *prev = dummyNode;
        for (int i = 0; i < left - 1; i++) {
            prev = prev->next;
        }

        ListNode *curr = prev->next;
        for (int i = 0; i < right - left; i++) {
            ListNode *next = curr->next;
            curr->next = next->next;
            next->next = prev->next;
            prev->next = next;
        }

        return dummyNode->next;
    }
};