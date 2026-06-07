#include <stdbool.h>
#include <stdlib.h>

typedef int ElemType;

// 定义单链表结点类型
typedef struct node{
    ElemType data;      // 数据域
    struct node *next;  // 直接后继
    struct node *prior;  // 直接前驱
} DuLNode, * DuLinkList;

// 构造一个空的线性表 L
void InitList(DuLinkList *L) {
    // 创建头结点，头指针指向头结点
    *L = (DuLNode *)malloc(sizeof(DuLNode));
    // 头结点的数据域不需要存储任何数据
    // 空表
    (*L)->next =NULL;
    // 初始化直接前驱为空
    (*L)->prior = NULL;
}

// 销毁线性表 L
void DestroyList(DuLinkList L) {
    // 第一步：先释放所有非头结点内存空间
    DuLNode *p = L->next;
    while (p) {
        DuLNode *q = p;
        p = p->next;
        free(q);
    }

    // 第二步：再释放头结点内存空间
    free(L);
}

// 返回指向第 i 个结点的结点指针
DuLNode * GetLNode(DuLinkList L, int i) {
    // 如果 i 小于 0，那么第 i 个结点肯定不存在
    // 注意：第 0 个结点是头结点
    if (i < 0) return NULL;

    // 定义结点指针 p 指向头结点
    DuLNode *p = L;
    // 初始化变量 j 为 0,
    int j = 0;

    // 如果 p 不为空且 j 小于 i，说明还没找到第 i 个结点，得继续找
    // 如果 p 指向空且 j 小于 i，说明不存在第 i 个结点
    while (p && j < i) {
        p = p->next;
        j++;
    }

    return p;
}

// 在线性表 L 中第 i 个位置之前插入新的数据元素 e
bool ListInsert(DuLinkList L, int i, ElemType e) {
    // 找到第 i - 1 个结点
    DuLNode *p = GetLNode(L, i - 1);

    // 没找到第 i - 1 个结点
    if (!p) return false;

    // 创建新结点，并将其插入到第 i 个结点位置
    DuLNode *s = (DuLNode *)malloc(sizeof(DuLNode));
    s->data = e;

    // 维护 s 和 p->next 之间的关系
    s->next = p->next;
    if (p->next) p->next->prior = s;

    // 维护 s 和 p 之间的关系
    s->prior = p;
    p->next = s;
    return true;
}

// 删除线性表 L 的第 i 个数据元素
bool ListDelete(DuLinkList L, int i, ElemType *e) {
    // 找到第 i - 1 个结点
    DuLNode *p = GetLNode(L, i - 1);

    // 没找到第 i - 1 个结点，或者找到了，但它是最后一个结点
    if (!p || !p->next) return false;

    // 结点指针 q 指向删除的第 i 个节点
    DuLNode *q = p->next;
    if (e) *e = q->data;

    // 维护 p 结点和它的直接后继的直接后继结点的关系
    if (q->next) q->next->prior = p;
    p->next = q->next;
    
    // 释放要删除节点的主存空间
    free(q);
    return true;
}

// 修改线性表 L 的第 i 个数据元素为 e
// 时间复杂度：O(n)
// 空间复杂度：O(1)
bool ListUpdate(DuLinkList L, int i, ElemType e) {
    // 找到第 i 个结点位置
    DuLNode *p = GetLNode(L, i);

    // 没找到第 i 个结点
    if (!p) return false;

    // 设置第 i 个结点的值为 e
    p->data = e;
    return true;
}

// 查询线性表 L 是否为空
// 时间复杂度：O(1)
// 空间复杂度：O(1)
bool ListEmpty(DuLinkList L) {
    return L->next == NULL;
}

// 查询线性表 L 的长度
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int ListLength(DuLinkList L) {
    // 从头结点的下一个结点开始，遍历所有的结点
    // 每遍历一个结点，长度加 1
    DuLNode *p = L->next;
    int length = 0;
    while (p) {
        length++;
        p = p->next;
    }
    return length;
}

// 用 e 返回线性表 L 中第 i 个数据元素的值
// 时间复杂度：O(n)
// 空间复杂度：O(1)
bool GetElem(DuLinkList L, int i, ElemType *e) {
    // 找到第 i 个结点位置
    DuLNode *p = GetLNode(L, i);

    // 没找到第 i 个结点
    if (!p) return false;

    // 返回第 i 个结点的值
    *e = p->data;
    return true;
}

// 返回线性表 L 中第 1 个值与 e 相同的元素在 L 中的位置
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int LocateElem(DuLinkList L, ElemType e) {
    // 从首元结点（第一个结点）开始找
    DuLNode *p = L->next;

    // i 表示结点的位序，首元结点的位序等于 1
    int i = 1;

    while (p) {
        if (p->data == e) return i;
        p = p->next;
        i++;
    }

    // 没有找到，返回 0
    return 0;
}

// 对线性表 L 进行遍历打印每个元素
// 时间复杂度：O(n)
// 空间复杂度：O(1)
void TraverseList(DuLinkList L) {
    printf("curr LinkList: ");
    // 结点指针 p 指向首元结点
    DuLNode *p = L->next;
    while (p) {
         printf("%d -> ", p->data);
         p = p->next;
    }
    printf("NULL\n");
}

// 头插法创建 n 个结点的双向链表
// 时间复杂度：O(n)
void CreateList_HeadInsert(DuLinkList L, int n) {
    DuLNode *s;
    int x;
    for (int i = 0; i < n; i++) {
        // 创建新结点
        s = (DuLNode *)malloc(sizeof(DuLNode));

        // 从终端输入数据
        scanf("%d", &x);
        s->data = x;

        // 将新结点插入双向链表头部
        // 维护 s 和头结点的直接后继之间的关系
        s->next = L->next;
        if (L->next) L->next->prior = s;

        // 维护 s 和头结点之间的关系
        s->prior = L;
        L->next = s;
    }
}

// 尾插法创建 n 个结点的双向链表
// 时间复杂度：O(n)
void CreateList_TailInsert(DuLinkList L, int n) {
    DuLNode *s, *tail = L;
    int x;
    for (int i = 0; i < n; i++) {
        // 创建新结点
        s = (DuLNode *)malloc(sizeof(DuLNode));

        // 从终端输入数据
        scanf("%d", &x);
        s->data = x;

        // 将新结点插入双向链表尾部
        s->next = NULL;     // 新结点的 next 指向空
        tail->next = s;     // 尾结点的 next 指向新结点
        s->prior = tail;    // 新结点的直接前驱指向最后一个结点
        tail = s;           // 将新结点设置为尾结点
    }
}