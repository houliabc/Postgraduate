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
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head || !head->next || k == 0 || k == 1) return head;

        ListNode* dummyNode = new ListNode(-1);
        dummyNode->next = head;

        ListNode *prev = dummyNode;
        ListNode *first = head;
        ListNode *last = first;
        while (first) {
            for (int i = 0; i < k - 1; i++) {
                last = last->next;
                if (!last) return dummyNode->next;
            }
            ListNode *next = last->next;
            last->next = nullptr;

            reverse(first);

            prev->next = last;
            first->next = next;

            prev = first;
            first = next;
            last = first;
        }
        return dummyNode->next;
    }

    ListNode* reverse(ListNode* head) {
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
};