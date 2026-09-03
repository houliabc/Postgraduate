#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef int ElemType;
typedef struct {
    ElemType *data;  // 如果是顺序存储，因为用的是数组，所以一开始就要开辟好空间
    int front;
    int rear;
    int capacity;
} SqQueue;

// 构造一个容量为 n 的空队列 Q
void InitQueue(SqQueue *Q, int n) {
    Q->data = (ElemType*)malloc(sizeof(ElemType) * n);
    Q->front = 0;
    Q->rear = 0;
    Q->capacity = n;
}

// 销毁队列 Q
void DestroyQueue(SqQueue *Q) {
    if(Q)
        // 主要是释放掉队列的数组所占的空间
        free(Q->data);
}

// 将 Q 清为空队列
void ClearQueue(SqQueue *Q) {
    // 用头尾指针为0来表示队列空，并不是真正意义的情况占用空间
    Q->rear = 0;
    Q->front = 0;
}

// 若 Q 为空队列，则返回 true，否则返回 false
bool QueueEmpty(SqQueue *Q) {
    return Q->rear == Q->front;
}

// 返回 Q 的元素个数，即队列的长度
int QueueLength(SqQueue *Q) {
    return (Q->rear - Q->front + Q->capacity) % Q->capacity;
}

// 初始条件：Q 为非空队列
// 操作结果：返回 Q 的队头元素，用 e 返回其值
bool GetHead(SqQueue *Q, ElemType *e) {
    if (QueueEmpty(Q))
        return false;
    *e = Q->data[Q->front];
    return true;
}

// 插入元素 e 为 Q 的新的队尾元素
bool EnQueue(SqQueue *Q, ElemType e) {
    // 满了则不能插入了
    if (((Q->rear + 1) % Q->capacity) == Q->front)
        return false;
    //先放元素再后移指针
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear + 1) % Q->capacity;
    return true;
}

// 初始条件：Q 为非空队列
// 操作结果：删除 Q 的队头元素，并用 e 返回其值
bool DeQueue(SqQueue *Q, ElemType *e) {
    // 判断是否为空
    if (QueueEmpty(Q))
        return false;
    if (e)
        *e = Q->data[Q->front];
    Q->front = (Q->front + 1) % Q->capacity;
    return true;
}

// 初始条件：Q 已存在且非空
// 操作结果：从队头到队尾，依次对 Q 的每个数据元素访问
void QueueTraverse(SqQueue *Q) {
    if (QueueEmpty(Q))
        return;
    for (int i = Q->front; i != Q->rear; i = (i + 1) % Q->capacity) {  // 注意这里i的变化用的是i+1，而不是修改Q的指针
        if( (i + 1) % Q->capacity == Q->rear ){
            printf("%d", Q->data[i]);
        }else{
            printf("%d-", Q->data[i]);
        }
    }
    printf("\n");
}
