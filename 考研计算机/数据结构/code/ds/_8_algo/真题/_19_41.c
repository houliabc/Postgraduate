#include <stdio.h>

typedef struct node {
    int data;
    struct node *next;
} NODE;

// 方法一：使用辅助数组
void reLink(NODE *head, int n) {
    int temp[n];
    // 将链表中的结点值拷贝到数组中
    NODE *curr = head->next;
    for (int i = 0; i < n; i++) {
        temp[i] = curr->data;
        curr = curr->next;
    }

    curr = head->next;
    int left = 0, right = n - 1;
    while (left <= right) {
        // 先排列一个前半部分的结点
        curr->data = temp[left];
        curr = curr->next;
        // 如果结点指向空了，则直接返回
        if (curr == NULL) return;
        // 再排列一个后半部分的结点
        curr->data = temp[right];
        curr = curr->next;

        left++;
        right--;
    }
}

// 反转单链表（不包含头结点），返回反转后链表的首元结点
NODE* reverse(NODE *head) {
    NODE *curr = head;
    NODE *prev = NULL;
    while (curr != NULL) {
        NODE *next = curr->next;
        // 反转 prev 和 curr
        curr->next = prev;

        prev = curr;
        curr = next;
    }
    return prev;
}

// 方法二：基于反转单链表实现
void reLink(NODE *head, int n) {
    // 找到单链表的中间结点
    NODE *slow = head, *fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // 至此，slow 指向中间结点
    // 先记住后半部分的第一个结点
    NODE *tmp = slow->next;
    // 如果后半部分链表是空的或者只有 1 个结点，直接返回
    if (tmp == NULL || tmp->next == NULL) return;
    // 将前后半部分的链表断开
    slow->next = NULL;

    // 原地反转后半部分的链表
    NODE *q = reverse(tmp); // q 指向反转后的链表的第一个结点

    // 重排前半部分和后半部分链表
    NODE *p = head->next;
    while (q != NULL) {
         NODE *nextp = p->next;
         p->next = q;
         p = nextp;

         NODE *nextq = q->next;
         q->next = p;
         q = nextq;
    }
}