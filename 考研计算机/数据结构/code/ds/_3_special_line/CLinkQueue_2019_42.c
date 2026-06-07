#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef int QElemType;

typedef struct QNode {
    QElemType data;
    struct QNode *next;
} QNode;

typedef struct  {
    QNode *front;       // 头指针
    QNode *rear;        // 尾指针
} CLinkQueue;


void InitQueue(CLinkQueue *Q) {
    // 头指针指向创建的新结点
    Q->front = (QNode *) malloc (sizeof(QNode));
    // 尾指针也指向这个新结点
    Q->rear = Q->front;
    // 空节点的 next 指针域指向自己，循环单链表
    Q->front->next = Q->front;
}

// 入队操作
// 时间复杂度：O(1)
bool EnQueue(CLinkQueue *Q, QElemType e) {
    if (Q->rear->next == Q->front) { // 队满
        // 在 rear 后面插入一个空结点
        QNode *p = (QNode *) malloc (sizeof(QNode));
        p->next = Q->rear->next;
        Q->rear->next = p;
    }
    // 将入队的元素赋值到 rear 结点
    Q->rear->data = e;
    // rear 往后走一步
    Q->rear = Q->rear->next;
    return true;
}

// 出队操作
// 时间复杂度：O(1)
bool DeQueue(CLinkQueue *Q, QElemType *e) {
    // 队空，出队失败
    if (Q->front == Q->rear) return false;
    if (e) *e = Q->front->data;
    Q->front = Q->front->next;
    return true;
}