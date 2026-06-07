/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode1(ListNode *headA, ListNode *headB) {
        if (!headA || !headB) return nullptr;
        unordered_set<ListNode*> set;
        while (headA) {
            set.insert(headA);
            headA = headA->next;
        }

        while (headB) {
            if (set.count(headB)) return headB;
            headB = headB->next;
        }

        return nullptr;
    }

    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (!headA || !headB) return nullptr;
        ListNode *a = headA;
        ListNode *b = headB;

        while (a != b) {
            a = (a == nullptr) ? headB : a->next;
            b = (b == nullptr) ? headA : b->next;
        }

        return a;
    }
};