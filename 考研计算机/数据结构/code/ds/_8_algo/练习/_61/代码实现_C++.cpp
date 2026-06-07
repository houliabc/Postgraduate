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
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr || head->next == nullptr || k == 0) return head;
        int len = 1;
        ListNode *lastNode = head;
        while (lastNode->next != nullptr) {
            len++;
            lastNode = lastNode->next;
        }
        if (k % len == 0) return head;
        k = k % len;

        ListNode *newTail = head;
        for (int i = 0; i < len - k - 1; i++) {
            newTail = newTail->next;
        }

        ListNode *newHead = newTail->next;
        newTail->next = nullptr;
        lastNode->next = head;

        return newHead;
    }
};