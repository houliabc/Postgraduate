#include "MaxHeap.c"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// 优先队列结构（基于最大堆）
typedef struct {
    MaxHeap *H;
} PriorityQueue;

// 初始化优先队列
void initPriorityQueue(PriorityQueue *pq, int capacity) {
    pq->H = (MaxHeap*)malloc(sizeof(MaxHeap));
    InitMaxHeap(pq->H, capacity);
}

// 销毁优先队列
void destroyPriorityQueue(PriorityQueue *pq) {
    DestoryMaxHeap(pq->H);
    free(pq->H);
    pq->H = NULL;
}

// 判空
bool isPriorityQueueEmpty(PriorityQueue *pq) {
    return MaxHeapEmpty(pq->H);
}

// 获取队首元素（最大值）
bool getFront(PriorityQueue *pq, ElemType *e) {
    return extractMax(pq->H, e);
}

// 入队
bool enqueue(PriorityQueue *pq, ElemType e) {
    return MaxHeapInsert(pq->H, e);
}

// 出队
bool dequeue(PriorityQueue *pq, ElemType *e) {
    return MaxHeapDelMax(pq->H, e);
}

int main() {
    // 创建优先队列，容量为 10
    PriorityQueue pq;
    initPriorityQueue(&pq, 10);

    // 插入一些元素
    enqueue(&pq, 30);
    enqueue(&pq, 10);
    enqueue(&pq, 50);
    enqueue(&pq, 20);
    enqueue(&pq, 40);

    printf("优先队列中的元素（按优先级出队）:\n");
    while (!isPriorityQueueEmpty(&pq)) {
        int val;
        dequeue(&pq, &val);
        printf("%d ", val);
    }
    printf("\n");

    // 销毁队列
    destroyPriorityQueue(&pq);
    return 0;
}