#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "BiTree.h"

//- - - - - 队列的链式存储结构- - - - -
typedef BiTNode *ElemType;

typedef struct QNode {
    ElemType data;
    struct QNode *next;
} QNode;

typedef struct LinkQueue {
    QNode *rear;
    QNode *front;
    int length;
} LinkQueue;


// 构造一个空队列 Q
void InitQueue(LinkQueue *Q) {
    // 创建头节点：用队头指向头节点
    Q->front = (QNode*)malloc(sizeof(QNode));
    // 队头队尾在同一处表示是队空
    Q->rear = Q->front;

    // 表示是没有一个结点的链表
    Q->front->next = NULL;
    Q->length = 0;
}

// 清空队列
// 时间复杂度是 O(n)，n 表示队列中的元素个数
void ClearQueue(LinkQueue *Q) {
    if (!Q)
        return;

    // 先不删除头节点（Q->front），而是从首元结点开始的结点
    QNode *p = Q->front->next, *ptr;
    while(p) {
        ptr = p;
        p = p->next;
        free(ptr);
    }
    Q->length = 0;
    Q->rear = Q->front;
    Q->front->next = NULL;
}

// 销毁队列
void DestroyQueue(LinkQueue *Q) {
    ClearQueue(Q);
    // 最后再删除头节点，注，无需删除Q，因为只给了头节点分配空间，Q无空间
    free(Q->front);
}

// 队列判空
// 时间复杂度是 O(1)
bool QueueEmpty(LinkQueue *Q) {
    return Q->front == Q->rear;
}

// 查询队列长度
// 时间复杂度是 O(1)
int QueueLength(LinkQueue *Q) {
    return Q->length;
}

// 拿到队首元素
// 时间复杂度是 O(1)
bool GetHead(LinkQueue *Q, ElemType *e) {
    if (QueueEmpty(Q))
        return false;
    *e = Q->front->next->data;
    return true;
}

// 入队操作——尾进头出记住了
// 时间复杂度是 O(1)
bool EnQueue(LinkQueue *Q, ElemType e) {
    // 链队无需判断是否满
    QNode *p = (QNode*)malloc(sizeof(QNode));

    p->data = e;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;

    Q->length++;
    return true;
}

// 出队操作
// 时间复杂度是 O(1)
bool DeQueue(LinkQueue *Q, ElemType *e) {
    if (QueueEmpty(Q))
        return false;
    QNode *p = Q->front->next;
    if(e)
        *e = p->data;

    Q->front->next = p->next;
    // 如果当前队列只有一个元素，则将队列变为空队列
    if (!p->next)
        Q->rear = Q->front;
    
    free(p);
    Q->length--;
    return true;
}

// 遍历打印队列中所有元素
void QueueTraverse(LinkQueue *Q) {
    if (QueueEmpty(Q))
        return;
    QNode *p = Q->front->next;
    while (p) {
        printf("%d-", p->data);
        p = p->next;
    }
    printf("\n");
}
