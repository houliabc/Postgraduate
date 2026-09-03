#include "MaxHeap.c"

typedef struct {
    MaxHeap *H;
} PriorityQueue;

// 优先队列入队
// 时间复杂度：O(logn)
bool enqueue(PriorityQueue *pq, HElemType e) {
    return MaxHeapInsert(pq->H, e);
}

// 优先队列出队
// 时间复杂度：O(logn)
bool dequeue(PriorityQueue *pq, HElemType *e) {
    return MaxHeapDelMax(pq->H, e);
}

