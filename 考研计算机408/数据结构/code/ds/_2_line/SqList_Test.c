#include <stdio.h>
#include "SqList.c"

int main() {
    SqList L;
    InitList(&L);

    ListInsert(&L, 1, 4);
    ListInsert(&L, 2, 6);
    ListInsert(&L, 3, 7);
    ListInsert(&L, 4, 8);

    TraverseList(&L);

    ListInsert(&L, 2, 10);
    TraverseList(&L);

    ElemType e;
    ListDelete(&L, 3, &e);
    printf("delete ele is %d\n", e);
    TraverseList(&L);

    ListUpdate(&L, 3, 99);
    TraverseList(&L);

    DestroyList(&L);

    return 0;
}