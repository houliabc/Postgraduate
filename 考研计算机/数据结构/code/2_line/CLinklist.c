#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// 循环单链表版本
typedef int ElemType;
typedef struct Node {
    ElemType data;
    struct Node *next;
} LNode, *CLinkList;

// 构造空的线性表
void InitList(CLinkList *L) {  // 这里要修改L，所以以指针传入进来
    // 创建头节点
    *L = (LNode*)malloc(sizeof(LNode));
    (*L)->next = *L;
}

// 销毁线性表
void DestroyList(CLinkList L) {
    LNode *p = L->next;
    while (p != L) {
        LNode *q = p->next;
        free(p);
        p = q;
    }
    free(L);
}

// 返回指向第 i 个结点的指针
LNode *GetLNode(CLinkList L, int i) {
    // 这里是i<0，因为第0个结点是头节点
    if (i < 0)
        return NULL;
    LNode *p = L;
    int j = 0;
    while (p->next != L && j < i) {
        p = p->next;
        j++;
    }
    if (j == i)  // 找到了结点
        return p;
    return NULL;  // 没找到结点
}

// 在第 i 个位置之前插入元素 e
bool ListInsert(CLinkList L, int i, ElemType e) {
    // 找到第i个位置的前一个位置
    LNode *p = GetLNode(L, i - 1);

    if (!p)
        return false;

    LNode *s = (LNode*)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;

    return true;
}

// 删除第 i 个元素，用 e 返回其值
bool ListDelete(CLinkList L, int i, ElemType *e) {
    // 找到第i个位置的前一个位置
    LNode *p = GetLNode(L, i - 1);

    // 没找到第i-1个结点，或者是最后一个结点
    if (!p || !p->next)
        return false;

    if (e)
        *e = p->next->data;
    LNode *q = p->next;
    p->next = q->next;
    free(q);

    return true;
}

// 修改第 i 个元素的值为 e
bool ListUpdate(CLinkList L, int i, ElemType e) {
    // 找到第i个位置
    LNode *p = GetLNode(L, i);

    if (!p)
        return false;

    p->data = e;
    return true;
}

// 判断线性表是否为空
bool ListEmpty(CLinkList L) {
    return L->next == L;
}

// 返回线性表的长度
int ListLength(CLinkList L) {
    LNode *p = L->next;
    int j = 0;
    while (p != L) {
        p = p->next;
        j++;
    }
    return j;
}

// 用 e 返回第 i 个元素的值
bool GetElem(CLinkList L, int i, ElemType *e) {
    // 找到第i个位置
    LNode *p = GetLNode(L, i);
    if (!p)
        return false;

    if (e)
        *e = p->data;
    return true;
}

// 查找第一个等于 e 的元素的位序，未找到返回 0
int LocateElem(CLinkList L, ElemType e) {
    LNode *p = L->next;
    int j = 1;
    while (p != L) {
        if (p->data == e)
            return j;
        p = p->next;
        j++;
    }
    return 0;
}

// 遍历打印线性表
void TraverseList(CLinkList L) {
    LNode *p = L->next;
    while (p != L) {
        if (p->next != L)
            printf("%d -> ", p->data);
        else
            printf("%d\n", p->data);
        p = p->next;
    }
}

// 头插法创建n个结点的链表
void CreateList_HeadInsert(CLinkList L, int n) {
    for (int i = 0; i < n; i++) {
        LNode *s = (LNode*)malloc(sizeof(LNode));
        scanf("%d", &s->data);
        s->next = L->next;
        L->next = s;
    }
}

// 尾插法创建n个结点的链表
void CreateList_TailInsert(CLinkList L, int n) {
    LNode *tail = L;
    for (int i = 0; i < n; i++) {
        LNode *s = (LNode*)malloc(sizeof(LNode));
        scanf("%d", &s->data);
        s->next = L;
        tail->next = s;
        tail = s;
    }
}