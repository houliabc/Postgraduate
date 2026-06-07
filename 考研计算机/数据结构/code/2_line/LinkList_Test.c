#include <stdio.h>

#include "CLinkList.c"

int main() {
    CLinkList L;
    InitList(&L);

    ListInsert(L, 1, 10);
    ListInsert(L, 2, 100);
    ListInsert(L, 3, 1000);
    ListInsert(L, 4, 10000);

    TraverseList(L);

    ListInsert(L, 2, 99);
    TraverseList(L);

    ElemType e;
    ListDelete(L, 2, &e);
    printf("%d\n", e);
    TraverseList(L);

    DestroyList(L);

    CLinkList L2;
    InitList(&L2);
    CreateList_HeadInsert(L2, 5);
    TraverseList(L2);
    DestroyList(L2);


    CLinkList L3;
    InitList(&L3);
    CreateList_TailInsert(L3, 5);
    TraverseList(L3);
    DestroyList(L3);

    return 0;
}