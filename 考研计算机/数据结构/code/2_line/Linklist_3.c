#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// 版本3：去掉length，同时省去了头指针的定义（或者说合并在一起进行了定义）
typedef int ElemType;
typedef struct Node {
    ElemType data;
    struct Node *next;
} LNode, *LinkList;

// 构造空的线性表
void InitList(LinkList *L) {  // 这里要修改L，所以以指针传入进来
    // 创建头节点
    *L = (LNode*)malloc(sizeof(LNode));
    (*L)->next = NULL;
}

// 销毁线性表
void DestroyList(LinkList L) {
    LNode *p = L->next;
    while (p) {
        LNode *q = p->next;
        free(p);
        p = q;
    }
    free(L);
}

// 返回指向第 i 个结点的指针
LNode *GetLNode(LinkList L, int i) {
    if (i < 0)
        return NULL;
    LNode *p = L;
    int j = 0;
    while (p && j < i) {
        p = p->next;
        j++;
    }
    return p;
}

// 在第 i 个位置之前插入元素 e
bool ListInsert(LinkList L, int i, ElemType e) {
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
bool ListDelete(LinkList L, int i, ElemType *e) {
    // 找到第i个位置的前一个位置
    LNode *p = GetLNode(L, i - 1);

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
bool ListUpdate(LinkList L, int i, ElemType e) {
    // 找到第i个位置
    LNode *p = GetLNode(L, i);

    if (!p)
        return false;

    p->data = e;
    return true;
}

// 判断线性表是否为空
bool ListEmpty(LinkList L) {
    return L->next == NULL;
}

// 返回线性表的长度
int ListLength(LinkList L) {
    LNode *p = L->next;
    int j = 0;
    while (p) {
        p = p->next;
        j++;
    }
    return j;
}

// 用 e 返回第 i 个元素的值
bool GetElem(LinkList L, int i, ElemType *e) {
    // 找到第i个位置
    LNode *p = GetLNode(L, i);
    if (!p)
        return false;

    if (e)
        *e = p->data;
    return true;
}

// 查找第一个等于 e 的元素的位序，未找到返回 0
int LocateElem(LinkList L, ElemType e) {
    LNode *p = L->next;
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
void TraverseList(LinkList L) {
    LNode *p = L->next;
    while (p) {
        if (p->next)
            printf("%d -> ", p->data);
        else
            printf("%d\n", p->data);
        p = p->next;
    }
}

// 头插法创建n个结点的链表
void CreateList_HeadInsert(LinkList L, int n) {
    for (int i = 0; i < n; i++) {
        LNode *s = (LNode*)malloc(sizeof(LNode));
        scanf("%d", &s->data);
        s->next = L->next;
        L->next = s;
    }
}

// 尾插法创建n个结点的链表
void CreateList_TailInsert(LinkList L, int n) {
    LNode *tail = L;
    for (int i = 0; i < n; i++) {
        LNode *s = (LNode*)malloc(sizeof(LNode));
        scanf("%d", &s->data);
        s->next = NULL;
        tail->next = s;
        tail = s;
    }
}