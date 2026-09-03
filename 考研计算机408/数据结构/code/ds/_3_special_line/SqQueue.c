#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

//- - - - - 队列的顺序存储结构- - - - -
typedef int QElemType;

typedef struct  {
   QElemType *data;     // 数组基地址
   int front;           // 头指针
   int rear;            // 尾指针
   int capacity;        // 队列的容量
} SqQueue;

// 构造一个容量为 n 的空队列 Q
void InitQueue(SqQueue *Q, int n) {
    // 为队列分配一个最大容量为 n 的数组空间，data 指向数组空间的首地址
    Q->data = (QElemType *) malloc (n * sizeof(QElemType));

    // 头指针和尾指针置为零，表示队列为空
    Q->front = Q->rear = 0;

    // 初始化队列容量
    Q->capacity = n;
}

// 销毁队列
void DestroyQueue(SqQueue *Q) {
    // 释放队列占用的内存空间
    if (Q) free(Q->data);
}

// 清空队列
// 时间复杂度是 O(1)
void ClearQueue(SqQueue *Q) {
    // 头指针和尾指针置为零，表示队列为空
    Q->front = Q->rear = 0;
}

// 队列判空
// 时间复杂度是 O(1)
bool QueueEmpty(SqQueue *Q) {
    return Q->front == Q->rear;
}

// 查询队列长度
// 时间复杂度是 O(1)
int QueueLength(SqQueue *Q) {
    return (Q->rear - Q->front + Q->capacity) % Q->capacity;
}

// 拿到队首元素
// 时间复杂度是 O(1)
bool GetHead(SqQueue *Q, QElemType *e) {
    if (QueueEmpty(Q)) return false;
    *e = Q->data[Q->front];
    return true;
}

// 入队操作
// 时间复杂度是 O(1)
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

// 出队操作
// 时间复杂度是 O(1)
bool DeQueue(SqQueue *Q, QElemType *e) {
    // 队空，则出队失败
    if (Q->front == Q->rear) return false;

    // 如果需要返回出队的元素，则保存返回
    if (e) *e = Q->data[Q->front];

    // 队头指针加 1
    Q->front = (Q->front + 1) % Q->capacity;
    return true;
}

// 遍历打印队列中所有元素
void QueueTraverse(SqQueue *Q) {
    printf("curr queue front: ");
    int i = Q->front;
    while (i != Q->rear) {
        printf("%d, ", Q->data[i]);
        i = (i + 1) % Q->capacity;
    }
    printf("\n");
}


int main() {
    SqQueue queue;
    InitQueue(&queue, 6);

    EnQueue(&queue, 10);
    EnQueue(&queue, 100);
    EnQueue(&queue, 1000);
    EnQueue(&queue, 10000);

    printf("queue length = %d\n", QueueLength(&queue));
    QueueTraverse(&queue);

    DeQueue(&queue, NULL);
    QueueTraverse(&queue);

    DestroyQueue(&queue);
}