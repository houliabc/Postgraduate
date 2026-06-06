#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INIT_MAX_SIZE 10

typedef int ElemType;

typedef struct Sqlist
{
    ElemType *data; // 存储空间的首地址
    int length;
} Sqlist;

// 构造一个空的线性表 L
bool InitList(Sqlist *L) {
    L->data = (ElemType*)malloc(sizeof(ElemType) * INIT_MAX_SIZE);
    if (L->data == NULL)  // 规范写法，防止野指针
        return false;
    L->length = 0;
    return true;
}

// 销毁线性表 L
void DestroyList(Sqlist *L) {
    if (L && L->data) {
        free(L->data);
        L->data = NULL;
    }
    L->length = 0;
}

// 在线性表L中第i个位置之前插入新的数据元素e
bool ListInsert(Sqlist *L, int i, ElemType e) {
    // 先判断越界情况
    if (i < 1 || i > L->length + 1 || L->length >= INIT_MAX_SIZE)
        return false;
    // 往后移然后插入第i个位置
    for (int j = L->length; j >= i; j--) {
        L->data[j] = L->data[j - 1];
    }
    L->data[i - 1] = e;
    L->length++;
    return true;
}

// 删除线性表L的第i个数据元素
bool ListDelete(Sqlist *L, int i, ElemType *e) {
    // 先判断越界情况
    if (i < 1 || i > L->length)
        return false;
    if (e)
        *e = L->data[i - 1];
    for (int j = i - 1; j < L->length - 1; j++) {
        L->data[j] = L->data[j + 1];
    }
    L->length--;
    return true;
}

// 遍历线性表
void TraverseList(Sqlist *L) {
    printf("curr Sqlist: ");
    for (int i = 0; i < L->length; i++) {
        if (i == 0)
            printf("(%d,", L->data[i]);
        else if (i == L->length - 1)
            printf("%d)\n", L->data[i]);
        else
            printf("%d,", L->data[i]);
    }
}

// 修改线性表L的第i个数据元素为e
bool ListUpdate(Sqlist *L, int i, ElemType e) {
    // 先判断越界情况
    if (i < 1 || i > L->length)
        return false;
    L->data[i - 1] = e;
    return true;
}

// 查询线性表L是否为空
bool ListEmpty(Sqlist *L) {
    return L->length == 0;
}

// 查询线性表L的长度
int ListLength(Sqlist *L) {
    return L->length;
}

// 用e返回线性表L中第i个数据元素的值
bool ListGetElem(Sqlist *L, int i, ElemType *e) {
    // 先判断越界情况
    if (i < 1 || i > L->length)
        return false;
    *e = L->data[i - 1];
    return true;
}

// 返回线性表L中第1个值与e相同的元素在L中的位置
int ListLocateElem(Sqlist *L, ElemType e) {
    for (int i = 0; i < L->length; i++) {
        if (L->data[i] == e)
            return i + 1;
    }
    return -1;
}