#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef int ElemType;

// 定义单链表结点类型
typedef struct node{
    ElemType data;      // 数据域
    struct node *next;  // 指针域
} LNode, * CLinkList;

// 构造一个空的线性表 L
void InitList(CLinkList *L) {
    // 创建头结点，头指针指向头结点
    *L = (LNode *)malloc(sizeof(LNode));
    // 头结点的数据域不需要存储任何数据
    (*L)->next = *L; // 空表
}

// 销毁线性表 L
void DestroyList(CLinkList L) {
    // 第一步：先释放所有非头结点内存空间
    LNode *p = L->next;
    // 如果 p 指向了头结点，那么就说明遍历完了
    while (p != L) {
        LNode *q = p;
        p = p->next;
        free(q);
    }

    // 第二步：再释放头结点内存空间
    free(L);
}

// 返回指向第 i 个结点的结点指针
LNode * GetLNode(CLinkList L, int i) {
    // 如果 i 小于 0，那么第 i 个结点肯定不存在
    // 注意：第 0 个结点是头结点
    if (i < 0) return NULL;

    // 定义结点指针 p 指向头结点
    LNode *p = L;
    // 初始化变量 j 为 0,
    int j = 0;

    // 判断当前结点不是最后一个结点且不是第 i 个结点
    while (p->next != L && j < i) {
        p = p->next;
        j++;
    }

    // 找到了第 i 个结点
    if (j == i) return p;
    return NULL;
}

// 在线性表 L 中第 i 个位置之前插入新的数据元素 e
bool ListInsert(CLinkList L, int i, ElemType e) {
    // 找到第 i - 1 个结点
    LNode *p = GetLNode(L, i - 1);

    // 没找到第 i - 1 个结点
    if (!p) return false;

    // 创建新结点，并将其插入到第 i 个结点位置
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e;

    s->next = p->next;
    p->next = s;
    return true;
}

// 删除线性表 L 的第 i 个数据元素
bool ListDelete(CLinkList L, int i, ElemType *e) {
    // 找到第 i - 1 个结点
    LNode *p = GetLNode(L, i - 1);

    // 没找到第 i - 1 个结点，或者找到了，但它是最后一个结点
    if (!p || p->next == L) return false;

    // 结点指针 q 指向删除的第 i 个节点
    LNode *q = p->next;
    if (e) *e = q->data;

    p->next = q->next;
    q->next = NULL;
    free(q);
    return true;
}

// 修改线性表 L 的第 i 个数据元素为 e
// 时间复杂度：O(n)
// 空间复杂度：O(1)
bool ListUpdate(CLinkList L, int i, ElemType e) {
    // 找到第 i 个结点位置
    LNode *p = GetLNode(L, i);

    // 没找到第 i 个结点
    if (!p) return false;

    // 设置第 i 个结点的值为 e
    p->data = e;
    return true;
}

// 查询线性表 L 是否为空
// 时间复杂度：O(1)
// 空间复杂度：O(1)
bool ListEmpty(CLinkList L) {
    return L->next == L;
}

// 查询线性表 L 的长度
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int ListLength(CLinkList L) {
    // 从头结点的下一个结点开始，遍历所有的结点
    // 每遍历一个结点，长度加 1
    LNode *p = L->next;
    int length = 0;
    // 如果 p 指向头指针，说明结点遍历完了
    while (p != L) {
        length++;
        p = p->next;
    }
    return length;
}

// 用 e 返回线性表 L 中第 i 个数据元素的值
// 时间复杂度：O(n)
// 空间复杂度：O(1)
bool GetElem(CLinkList L, int i, ElemType *e) {
    // 找到第 i 个结点位置
    LNode *p = GetLNode(L, i);

    // 没找到第 i 个结点
    if (!p) return false;

    // 返回第 i 个结点的值
    *e = p->data;
    return true;
}

// 返回线性表 L 中第 1 个值与 e 相同的元素在 L 中的位置
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int LocateElem(CLinkList L, ElemType e) {
    // 从首元结点（第一个结点）开始找
    LNode *p = L->next;

    // i 表示结点的位序，首元结点的位序等于 1
    int i = 1;

    while (p != L) {
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
void TraverseList(CLinkList L) {
    printf("curr CLinkList: ");
    // 结点指针 p 指向首元结点
    LNode *p = L->next;
    while (p != L) {
         printf("%d -> ", p->data);
         p = p->next;
    }
    printf("%d\n", L->data);
}

// 头插法创建 n 个结点的单链表
// 时间复杂度：O(n)
void CreateList_HeadInsert(CLinkList L, int n) {
    LNode *s;
    int x;
    for (int i = 0; i < n; i++) {
        // 创建新结点
        s = (LNode *)malloc(sizeof(LNode));

        // 从终端输入数据
        scanf("%d", &x);
        s->data = x;

        // 将新结点插入单链表头部
        s->next = L->next; // 新结点的 next 指向头结点的下一个结点
        L->next = s;       // 头结点的 next 指向新结点
    }
}

// 尾插法创建 n 个结点的单链表
// 时间复杂度：O(n)
void CreateList_TailInsert(CLinkList L, int n) {
    LNode *s, *tail = L;
    int x;
    for (int i = 0; i < n; i++) {
        // 创建新结点
        s = (LNode *)malloc(sizeof(LNode));

        // 从终端输入数据
        scanf("%d", &x);
        s->data = x;

        // 将新结点插入单链表尾部
        s->next = L;     // 新结点的 next 指向头结点
        tail->next = s;     // 尾结点的 next 指向新结点
        tail = s;           // 将新结点设置为尾结点
    }
}

int main() {
    CLinkList L;

    InitList(&L);

    ListInsert(L, 1, 10);
    ListInsert(L, 2, 100);
    ListInsert(L, 3, 1000);
    ListInsert(L, 4, 10000);

    TraverseList(L);

    ListInsert(L, 2, 999);
    TraverseList(L);
    
    ElemType e;
    ListDelete(L, 3, &e);

    printf("delete element is %d\n", e);
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