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
    static bool cmp(ListNode* node1, ListNode* node2) {
        return node1->val > node2->val;
    }

    // 优先队列
    // 时间复杂度：O(k*n*logk)
    // 空间复杂度：O(k)
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.size() == 0) return nullptr;
        // 使用小顶堆
        priority_queue<ListNode*, vector<ListNode*>, decltype(&cmp)> pq(cmp);

        for (auto node : lists) {
            // bug 修复：防止链表为空
            if (node == nullptr) continue;
            pq.push(node);
        }

        ListNode dummyNode;
        ListNode* curr = &dummyNode;
        while (!pq.empty()) {
            ListNode* minNode = pq.top();
            pq.pop();
            curr->next = minNode;
            curr = curr->next;
            if (minNode->next != nullptr) {
                pq.push(minNode->next);
            }
        }

        return dummyNode.next;
    }

    // 分治思想
    // 时间复杂度：O(k*n*logk)
    // 空间复杂度：O(logk)
    ListNode* mergeKLists2(vector<ListNode*>& lists) {
        if (lists.size() == 0) return nullptr;

        return merge(lists, 0, lists.size() - 1);
    }

    ListNode* merge(vector<ListNode*>& lists, int left, int right) {
        if (left == right) return lists[left];

        int mid = left + (right - left) / 2;

        ListNode *mergedLeftList = merge(lists, left, mid);
        ListNode *mergedRightList = merge(lists, mid + 1, right);

        return mergeTwoLists(mergedLeftList, mergedRightList);
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
};