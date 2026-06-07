#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "BiTree.h"

//- - - - - 队列的链式存储结构- - - - -
typedef BiTNode * QElemType;

typedef struct QNode {
    QElemType data;
    struct QNode *next;
} QNode;

typedef struct  {
    QNode *front;     //头指针
    QNode *rear;      //尾指针
    int length;       // 队列中元素个数
} LinkQueue;

// 构造一个空队列 Q
void InitQueue(LinkQueue *Q) {
    // 生成新结点作为头结点，队头和队尾指针指向此结点
    Q->front = (QNode *) malloc (sizeof(QNode));
    Q->rear = Q->front;

    // 头结点的指针域置空
    Q->front->next = NULL;

    Q->length = 0;
}

// 清空队列
// 时间复杂度是 O(n)，n 表示队列中的元素个数
void ClearQueue(LinkQueue *Q) {
    if (!Q) return;

    // 遍历释放除了头结点的所有结点占的内存空间
    QNode *q = Q->front->next;
    while (q) {
        QNode *p = q;
        q = q->next;
        free(p);
    }
    // 队头和队尾指针指向头结点
    Q->rear = Q->front;
}

// 销毁队列
void DestroyQueue(LinkQueue *Q) {
    if (!Q) return;
    ClearQueue(Q);
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
bool GetHead(LinkQueue *Q, QElemType *e) {
    if (QueueEmpty(Q)) return false;
    *e = Q->front->next->data;
    return true;
}

// 入队操作
// 时间复杂度是 O(1)
bool EnQueue(LinkQueue *Q, QElemType e) {
    // 为入队元素分配结点空间，用指针p指向
    QNode *p = (QNode *) malloc (sizeof(QNode));
    // 如果内存不够，入队失败
    if (!p) return false;

    // 将新结点数据域置为e
    p->data = e;

    // 将新结点插入到队尾
    p->next = NULL;
    Q->rear->next = p;

    // 修改队尾指针为 p
    Q->rear = p;

    Q->length++;

    return true;
}

// 出队操作
// 时间复杂度是 O(1)
bool DeQueue(LinkQueue *Q, QElemType *e) {
    // 队空，则出队失败
    if (QueueEmpty(Q)) return false;

    if (e) *e = Q->front->next->data;

    // 临时保存队头元素的空间，以备释放
    QNode *p = Q->front->next;

    // 修改头结点的指针域，指向首元结点下一个结点
    Q->front->next = p->next;

    // 判断出队元素是否为最后一个元素，若是，则将队尾指针重新赋值，指向头结点
    if (p == Q->rear) Q->rear = Q->front;

    // 释放原队头元素的空间
    free(p);

    Q->length--;
    return true;
}

// 遍历打印队列中所有元素
void QueueTraverse(LinkQueue *Q) {
    printf("curr queue front: ");
    QNode *p = Q->front->next;
    while (p) {
        printf("%c, ", p->data->data);
        p = p->next;
    }
    printf("\n");
}