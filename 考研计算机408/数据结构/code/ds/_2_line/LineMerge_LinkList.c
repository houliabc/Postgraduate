#include <stdio.h>

#include "LinkList.c"

// 空间复杂度：O(1)
// 时间复杂度：O(n × max(m, n)) 
void mergeList(LinkList A, LinkList B) {
    int m = ListLength(A);
    int n = ListLength(B);

    ElemType e;
    for (int i = 1; i <= n; i++) {
        GetElem(B, i, &e);
        if (!LocateElem(A, e)) {
            ListInsert(A, ++m, e);
        }
    }
}

// 时间复杂度：O(m + n) = O(max(m, n))
// 空间复杂度：O(1)
void mergeOrderedList(LinkList A, LinkList B, LinkList C) {
    // C 的尾指针 tail，初始时，指向 C 的头结点
    LNode *tail = C;
    // 指针 a 和 b 分别指向 A 和 B 的首元结点
    LNode *a = A->next, *b = B->next;

    while (a && b) { // 只要 a 和 b 不是指向空，就要比较
        if (a->data < b->data) {
            // 将 a 放到 C 的尾部
            tail->next = a;
            tail = a;
            a = a->next;
        } else {
            // 将 b 放到 C 的尾部
            tail->next = b;
            tail = b;
            b = b->next;
        }
    }

    tail->next = a ? a : b;

    free(A);
    free(B);
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