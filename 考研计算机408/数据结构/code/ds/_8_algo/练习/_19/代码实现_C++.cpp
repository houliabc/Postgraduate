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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummyNode = new ListNode(-1);
        dummyNode->next = head;

        ListNode *slow = dummyNode;
        ListNode *fast = dummyNode;

        while (n-- >= 0) {
            fast = fast->next;
        }

        while (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }

        ListNode *delNode = slow->next;
        slow->next = delNode->next;
        delNode->next = nullptr;

        return dummyNode->next;
    }
};