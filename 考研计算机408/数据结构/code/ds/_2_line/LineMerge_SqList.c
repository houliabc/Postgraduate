#include <stdio.h>

#include "SqList.c"

// 空间复杂度：O(1)
// 时间复杂度：O(m × n) 
void mergeList(SqList *A, SqList *B) {
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

// 合并两个有序的顺序表
// 时间复杂度：O(m + n) = O(max(m, n))
// 空间复杂度：O(m + n)
void mergeOrderedList(SqList *A, SqList *B, SqList *C) {
    int m = A->length, n = B->length;

    // 初始化一个长度为 m + n 的空的顺序表
    C->data = (ElemType*)malloc(sizeof(ElemType) * (m + n));

    // a、b、c 指向三个顺序表对应数组的第一个元素
    int a = 0, b = 0, c = 0;
    while (a < m && b < n) {
        // 如果 A 的元素小于 B 的元素，则将 A 的元素放到 C 中
        if (A->data[a] < B->data[b])  
            C->data[c++] = A->data[a++];
        else 
            C->data[c++] = B->data[b++];    // 否则，将 B 的元素放到 C 中
    }

    // 如果 A 中还有元素，那么直接全部放到 C 中
    while (a < m) C->data[c++] = A->data[a++];
    // 如果 B 中还有元素，那么直接全部放到 C 中
    while (b < n) C->data[c++] = B->data[b++];

    // 合并之后的顺序表长度为 m + n
    C->length = m + n;
}

int main() {
    // ------------------  合并线性表 -------------------
    SqList A;
    InitList(&A);
    ListInsert(&A, 1, 7);
    ListInsert(&A, 2, 5);
    ListInsert(&A, 3, 3);
    ListInsert(&A, 4, 11);
    ListInsert(&A, 5, 9);
    
    SqList B;
    InitList(&B);
    ListInsert(&B, 1, 2);
    ListInsert(&B, 2, 6);
    ListInsert(&B, 3, 3);
    ListInsert(&B, 4, 7);

    mergeList(&A, &B);

    TraverseList(&A);

    DestroyList(&A);
    DestroyList(&B);

    // ------------------  合并有序线性表 -------------------
    SqList A2;
    InitList(&A2);
    ListInsert(&A2, 1, 3);
    ListInsert(&A2, 2, 5);
    ListInsert(&A2, 3, 8);
    ListInsert(&A2, 4, 11);
    
    SqList B2;
    InitList(&B2);
    ListInsert(&B2, 1, 2);
    ListInsert(&B2, 2, 6);
    ListInsert(&B2, 3, 8);
    ListInsert(&B2, 4, 9);
    ListInsert(&B2, 5, 11);
    ListInsert(&B2, 6, 15);
    ListInsert(&B2, 7, 20);

    SqList C;
    mergeOrderedList(&A2, &B2, &C);

    TraverseList(&C);

    DestroyList(&A2);
    DestroyList(&B2);
    DestroyList(&C);
    
    return 0;
}