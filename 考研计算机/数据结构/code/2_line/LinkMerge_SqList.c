#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
# include "Sqlist.c"

// A与B取并集放到A处
void mergeList(SqList *A, SqList *B) {
    int a = ListLength(A), b = ListLength(B);
    ElemType e;
    for (int i = 1; i <= b; i++) {
        ListGetElem(B, i, &e);
        if (ListLocateElem(A, e)) {
            ListInsert(A, ++a, e);
        }
    }
}

// 按非递减去合并A和B到C
void mergeOrderedList(SqList *A, SqList *B, SqList *C) {
    int a = 0, b = 0, c = 0, m = A->length, n = B->length;
    C->data = (ElemType*)malloc(sizeof(ElemType) * (m + n));
    while (a < m && b < n) {
        if (A->data[a] < B->data[b])
            C->data[c++] = A->data[a++];
        else
            C->data[c++] = B->data[b++];
    }

    while (a < m) {
        C->data[c++] = A->data[a++];
    }

    while (b < n) {
        C->data[c++] = B->data[b++];
    }
    C->length = c;
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