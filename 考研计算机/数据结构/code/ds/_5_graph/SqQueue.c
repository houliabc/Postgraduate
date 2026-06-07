#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

//- - - - - 队列的顺序存储结构- - - - -
typedef int QElemType;

typedef struct  {
   QElemType *data;             //数组基地址
   int front;                   //头指针
   int rear;                    //尾指针
   int capacity;        // 队列的容量
} SqQueue;


void InitQueue(SqQueue *Q, int n) {
    // 为队列分配一个最大容量为 n 的数组空间，data 指向数组空间的首地址
    Q->data = (QElemType *) malloc (n * sizeof(QElemType));

    // 头指针和尾指针置为零，表示队列为空
    Q->front = Q->rear = 0;
    // 初始化队列容量
    Q->capacity = n;
}

void DestroyQueue(SqQueue *Q) {
    // 释放队列占用的内存空间
    if (Q) free(Q->data);
}

// 时间复杂度是 O(1)
void ClearQueue(SqQueue *Q) {
    // 头指针和尾指针置为零，表示队列为空
    Q->front = Q->rear = 0;
}

// 时间复杂度是 O(1)
bool QueueEmpty(SqQueue *Q) {
    return Q->front == Q->rear;
}

// 时间复杂度是 O(1)
int QueueLength(SqQueue *Q) {
    // 对于非循环队列，尾指针和头指针的差值便是队列长度
    // 而对于循环队列，差值可能为负数，所以需要将差值加上MAXQSIZE，然后与MAXQSIZE求余
    return (Q->rear - Q->front + Q->capacity) % Q->capacity;
}

// 时间复杂度是 O(1)
bool GetHead(SqQueue *Q, QElemType *e) {
    if (QueueEmpty(Q)) return false;
    *e = Q->data[Q->front];
    return true;
}

bool EnQueue(SqQueue *Q, QElemType e) {
    // 如果队列满了，则入队失败
    if ((Q->rear + 1) % Q->capacity == Q->front) 
        return false;

    // 新元素入队尾
    Q->data[Q->rear] = e;
    // 队尾指针加 1
    Q->rear = (Q->rear + 1) % Q->capacity;
    return true;
}

bool DeQueue(SqQueue *Q, QElemType *e) {
    // 队空，则出队失败
    if (QueueEmpty(Q)) return false;

    // 如果需要返回出队的元素，则保存返回
    if (e != NULL) *e = Q->data[Q->front];

    // 队头指针加 1
    Q->front = (Q->front + 1) % Q->capacity;
    return true;
}

void QueueTraverse(SqQueue *Q) {
    printf("curr queue front: ");
    int i = Q->front;
    while (i != Q->rear) {
        printf("%d, ", Q->data[i]);
        i = (i + 1) % Q->capacity;
    }
    printf("\n");
}