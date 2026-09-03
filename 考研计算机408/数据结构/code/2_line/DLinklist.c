#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// 双向链表
typedef int ElemType;
typedef struct Node {
    ElemType data;
    struct Node *prior;
    struct Node *next;
} DLNode, *DLinkList;

// 构造空的线性表
void InitList(DLinkList *L) {  // 这里要修改L，所以以指针传入进来
    // 创建头节点
    *L = (DLNode*)malloc(sizeof(DLNode));
    (*L)->prior = NULL;
    (*L)->next = NULL;
}

// 销毁线性表
void DestroyList(DLinkList L) {
    DLNode *p = L->next;
    while (p) {
        DLNode *q = p->next;
        free(p);
        p = q;
    }
    free(L);
}

// 返回指向第 i 个结点的指针
DLNode *GetDLNode(DLinkList L, int i) {
    if (i < 0)
        return NULL;
    DLNode *p = L;
    int j = 0;
    while (p && j < i) {
        p = p->next;
        j++;
    }
    return p;
}

// 在第 i 个位置之前插入元素 e
bool ListInsert(DLinkList L, int i, ElemType e) {
    // 找到第i个位置的前一个位置
    DLNode *p = GetDLNode(L, i - 1);

    if (!p)
        return false;

    DLNode *s = (DLNode*)malloc(sizeof(DLNode));
    s->data = e;

    s->next = p->next;
    s->prior = p;
    if (p->next)
        p->next->prior = s;
    p->next = s;

    return true;
}

// 删除第 i 个元素，用 e 返回其值
bool ListDelete(DLinkList L, int i, ElemType *e) {
    // 找到第i个位置的前一个位置
    DLNode *p = GetDLNode(L, i - 1);

    if (!p || !p->next)
        return false;

    if (e)
        *e = p->next->data;
    DLNode *q = p->next;
    if (p->next)
        q->next->prior = p;
    p->next = q->next;
    free(q);

    return true;
}

// 修改第 i 个元素的值为 e
bool ListUpdate(DLinkList L, int i, ElemType e) {
    // 找到第i个位置
    DLNode *p = GetDLNode(L, i);

    if (!p)
        return false;

    p->data = e;
    return true;
}

// 判断线性表是否为空
bool ListEmpty(DLinkList L) {
    return L->next == NULL;
}

// 返回线性表的长度
int ListLength(DLinkList L) {
    DLNode *p = L->next;
    int j = 0;
    while (p) {
        p = p->next;
        j++;
    }
    return j;
}

// 用 e 返回第 i 个元素的值
bool GetElem(DLinkList L, int i, ElemType *e) {
    // 找到第i个位置
    DLNode *p = GetDLNode(L, i);
    if (!p)
        return false;

    if (e)
        *e = p->data;
    return true;
}

// 查找第一个等于 e 的元素的位序，未找到返回 0
int LocateElem(DLinkList L, ElemType e) {
    DLNode *p = L->next;
    int j = 1;
    while (p) {
        if (p->data == e)
            return j;
        p = p->next;
        j++;
    }
    return 0;
}

// 遍历打印线性表
void TraverseList(DLinkList L) {
    DLNode *p = L->next;
    while (p) {
        if (p->next)
            printf("%d -> ", p->data);
        else
            printf("%d\n", p->data);
        p = p->next;
    }
}

// 头插法创建n个结点的链表
void CreateList_HeadInsert(DLinkList L, int n) {
    for (int i = 0; i < n; i++) {
        DLNode *s = (DLNode*)malloc(sizeof(DLNode));
        scanf("%d", &s->data);
        s->next = L->next;
        if (L->next)
            L->next->prior = s;
        L->next = s;
        s->prior = NULL;
    }
}

// 尾插法创建n个结点的链表
void CreateList_TailInsert(DLinkList L, int n) {
    DLNode *tail = L;
    for (int i = 0; i < n; i++) {
        DLNode *s = (DLNode*)malloc(sizeof(DLNode));
        scanf("%d", &s->data);
        
        s->next = NULL;
        s->prior = tail;
        tail->next = s;
        tail = s;
    }
}