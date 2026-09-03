/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    if (head == NULL) return NULL;
    struct ListNode* dummyNode = malloc(sizeof(struct ListNode));
    dummyNode->val = -1;
    dummyNode->next = head;

    struct ListNode* slow = dummyNode;
    struct ListNode* fast = dummyNode;

    // fast 先走 n + 1
    while (n-- >= 0) {
        fast = fast->next;
    }

    while (fast != NULL) {
        slow = slow->next;
        fast = fast->next;
    }

    struct ListNode* delNode = slow->next;
    slow->next = delNode->next;
    delNode->next = NULL;
    free(delNode);  // 释放被删除结点的内存

    head = dummyNode->next;
    free(dummyNode);
    return head;
}