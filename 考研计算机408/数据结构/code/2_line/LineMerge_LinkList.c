#include <stdio.h>
#include "LinkList_3.c"

// 时间复杂度：O(n × max(m, n)) 
void mergeList(LinkList A, LinkList B) {
    // 1. 找到A的尾节点
    LNode *tail = A;
    while (tail->next != NULL) {
        tail = tail->next;
    }

    // 2. 遍历B的节点，摘链 + 挂到A尾部（去重）
    LNode *cur = B->next;  // B的第一个节点
    LNode *temp;           // 临时指针，防止断链
    while (cur != NULL) {
        temp = cur->next;  // 先保存下一个节点

        // 3. A中不存在该元素，才拼接
        if (!LocateElem(A, cur->data)) {
            tail->next = cur;  // 挂到A尾部
            tail = cur;        // 尾指针后移
            cur->next = NULL;  // 关键！切断原链表，防止野指针
        }

        cur = temp;  // 遍历下一个
    }

    // 4. 关键！清空B链表，销毁时不会重复释放
    B->next = NULL;
}

// 时间复杂度：O(m + n) = O(max(m, n))
void mergeOrderedList(LinkList A, LinkList B, LinkList C) {
    LNode *c = C, *a = A->next, *b = B->next;
    while (a && b) {
        if (a->data < b->data) {
            c->next = a;
            a = a->next;
        }
        else {
            c->next = b;
            b = b->next;
        }
        c = c->next;
    }
    c->next = a ? a : b;

    free(A);free(B);
}


int main() {
    // ------------------  合并线性表 -------------------
    LinkList A;
    InitList(&A);
    ListInsert(A, 1, 7);
    ListInsert(A, 2, 5);
    ListInsert(A, 3, 3);
    ListInsert(A, 4, 11);
    ListInsert(A, 5, 9);
    
    LinkList B;
    InitList(&B);
    ListInsert(B, 1, 2);
    ListInsert(B, 2, 6);
    ListInsert(B, 3, 3);
    ListInsert(B, 4, 7);

    mergeList(A, B);

    TraverseList(A);

    DestroyList(A);
    DestroyList(B);

     // ------------------  合并有序线性表 -------------------
    LinkList A2;
    InitList(&A2);
    ListInsert(A2, 1, 3);
    ListInsert(A2, 2, 5);
    ListInsert(A2, 3, 8);
    ListInsert(A2, 4, 11);
    
    LinkList B2;
    InitList(&B2);
    ListInsert(B2, 1, 2);
    ListInsert(B2, 2, 6);
    ListInsert(B2, 3, 8);
    ListInsert(B2, 4, 9);
    ListInsert(B2, 5, 11);
    ListInsert(B2, 6, 15);
    ListInsert(B2, 7, 20);

    LinkList C;
    InitList(&C);
    mergeOrderedList(A2, B2, C);

    TraverseList(C);

    DestroyList(C);

    return 0;
}