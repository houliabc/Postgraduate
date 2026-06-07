#include <stdio.h>

#include "LinkList_2.c"

int main() {
    LinkList L;
    InitList(&L);

    ListInsert(&L, 1, 10);
    ListInsert(&L, 2, 100);
    ListInsert(&L, 3, 1000);
    ListInsert(&L, 4, 10000);

    TraverseList(&L);

    ListInsert(&L, 2, 99);
    TraverseList(&L);

    ElemType e;
    ListDelete(&L, 2, &e);
    printf("%d\n", e);
    TraverseList(&L);

    return 0;
}