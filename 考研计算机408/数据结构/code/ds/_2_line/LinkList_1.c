#include <stdbool.h>
#include <stdlib.h>

typedef int ElemType;

// 定义单链表结点类型
typedef struct node{
    ElemType data;      // 数据域
    struct node *next;  // 指针域
} LNode;

// 定义单链表
typedef struct {
    LNode* head;    // 头指针
    int length;     // 当前长度
} LinkList;

// 构造一个空的线性表 L
void InitList(LinkList *L) {
    // 创建头结点，头指针指向头结点
    L->head = (LNode *)malloc(sizeof(LNode));
    // 头结点的数据域不需要存储任何数据
    // 空表
    L->head->next =NULL;
    // 初始化当前长度为 0
    L->length = 0;
}

// 销毁线性表 L
void DestroyList(LinkList *L) {
    // 第一步：先释放所有非头结点内存空间
    LNode *p = L->head->next;
    while (p) {
        LNode *q = p;
        p = p->next;
        free(q);
    }

    // 第二步：再释放头结点内存空间
    free(L->head);
}

// 返回指向第 i 个结点的结点指针
LNode * GetLNode(LinkList *L, int i) {
    // 定义结点指针 p 指向头结点
    LNode *p = L->head;
    // 初始化变量 j 为 0,
    int j = 0;

    // 找到第 i 个结点位置
    while (j < i) {
        p = p->next;
        j++;
    }

    return p;
}

// 在线性表 L 中第 i 个位置之前插入新的数据元素 e
bool ListInsert(LinkList *L, int i, ElemType e) {
    // 判断如果位序 i 无效，则插入失败
    if (i < 1 || i > L->length + 1) 
        return false;

    // 找到第 i - 1 个结点
    LNode *p = GetLNode(L, i - 1);

    // 创建新结点，并将其插入到第 i 个结点位置
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e;

    s->next = p->next;
    p->next = s;

    L->length++;
    return true;
}

// 删除线性表 L 的第 i 个数据元素
bool ListDelete(LinkList *L, int i, ElemType *e) {
    // 判断如果位序 i 无效，则删除失败
    if (i < 1 || i > L->length) 
        return false;
    
    // 找到第 i - 1 个结点
    LNode *p = GetLNode(L, i - 1);

    // 结点指针 q 指向删除的第 i 个节点
    LNode *q = p->next;
    if (e) *e = q->data;

    p->next = q->next;
    q->next = NULL;
    free(q);

    L->length--;
    return true;
}

// 修改线性表 L 的第 i 个数据元素为 e
// 时间复杂度：O(n)
// 空间复杂度：O(1)
bool ListUpdate(LinkList *L, int i, ElemType e) {
    // 如果 i 的范围是无效，则修改失败
    if (i < 1 || i > L->length) 
        return false;
    
    // 找到第 i 个结点位置
    LNode *p = GetLNode(L, i);

    // 设置第 i 个结点的值为 e
    p->data = e;
    return true;
}

// 查询线性表 L 是否为空
// 时间复杂度：O(1)
// 空间复杂度：O(1)
bool ListEmpty(LinkList *L) {
    return L->length == 0;
}

// 查询线性表 L 的长度
// 时间复杂度：O(1)
// 空间复杂度：O(1)
int ListLength(LinkList *L) {
    return L->length;
}

// 用 e 返回线性表 L 中第 i 个数据元素的值
// 时间复杂度：O(n)
// 空间复杂度：O(1)
bool GetElem(LinkList *L, int i, ElemType *e) {
    // 如果 i 的范围是无效，则查询失败
    if (i < 1 || i > L->length) 
        return false;
    
    // 找到第 i 个结点位置
    LNode *p = GetLNode(L, i);

    // 返回第 i 个结点的值
    *e = p->data;
    return true;
}

// 返回线性表 L 中第 1 个值与 e 相同的元素在 L 中的位置
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int LocateElem(LinkList *L, ElemType e) {
    // 从首元结点（第一个结点）开始找
    LNode *p = L->head->next;

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
void TraverseList(LinkList *L) {
    printf("curr LinkList: ");
    // 结点指针 p 指向首元结点
    LNode *p = L->head->next;
    while (p) {
         printf("%d -> ", p->data);
         p = p->next;
    }
    printf("NULL\n");
}