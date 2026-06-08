#include <stdio.h>
#include "Sqlist.c"

int main() {
    Sqlist L;
    InitList(&L);

    ListInsert(&L, 1, 3);
    ListInsert(&L, 2, 1);
    ListInsert(&L, 1, 2);
    TraverseList(&L);

    ElemType e;
    ListDelete(&L, 2, &e);
    printf("e = %d\n", e);
    ListInsert(&L, 3, 1);
    TraverseList(&L);

    DestroyList(&L);
    return 0;
}