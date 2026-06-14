#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Heap.h"

// 堆的初始化
void InitMaxHeap(MaxHeap *H, int n) {
    H->data = (ElemType*)malloc(sizeof(ElemType) * n);
    H->capacity = n;
    H->heapSize = 0;
}

// 堆的销毁
void DestoryMaxHeap(MaxHeap *H) {
    if (H->data)
        free(H->data);
}

// 堆判空操作
// 时间复杂度：O(1)
bool MaxHeapEmpty(MaxHeap *H) {
    return H->heapSize == 0;
}

// 查询最大元素
// 时间复杂度：O(1)
bool extractMax(MaxHeap *H, ElemType *e) {
    if (MaxHeapEmpty(H))
        return false;
    *e = H->data[0];
    return true;
}

// 往堆中插入元素 e
// 时间复杂度：O(logn)
bool MaxHeapInsert(MaxHeap *H, ElemType e) {
    // TODO: 插入元素并上浮
    // 先判断是否满了
    if (H->capacity == H->heapSize)
        return false;
    int k = H->heapSize, parent;
    H->data[k] = e;
    H->heapSize++;
    // 如果不是根就一直进行比较，不符合就上浮
    while (k > 0) {
        // 父节点所在的下标
        parent = (k - 1) / 2;
        
        // 如果符合就跳出循环了
        if (H->data[parent] >= H->data[k])
            break;
        
        // 否则就交换，然后进行下一轮
        swap(&H->data[parent], &H->data[k]);
        k = parent;
    }
    return true;
}

// 将下标为 k 的结点做下沉操作
void MaxHeapSink(MaxHeap *H, int k) {
    int largest, right;
    while (k * 2 + 1 < H->heapSize) {
        largest = k * 2 + 1;
        right = k * 2 + 2;
        // 选择子元素最大的
        if (right < H->heapSize && H->data[right] > H->data[largest])
            largest = right;
        
        // 当前已经符合大顶堆的定义
        if (H->data[k] >= H->data[largest]) break;

        swap(&H->data[k], &H->data[largest]);
        k = largest;
    }
}

// 删除堆顶最大元素
// 时间复杂度：O(logn)
bool MaxHeapDelMax(MaxHeap *H, ElemType *e) {
    // TODO: 删除堆顶，返回元素值
    // 先判断是否空
    if (MaxHeapEmpty(H))
        return false;
    if (e)
        *e = H->data[0];
    // 将最后一个元素替换当前最大值
    H->data[0] = H->data[H->heapSize - 1];
    H->heapSize--;

    MaxHeapSink(H, 0);
    return true;
}

// 原地建堆操作
// 时间复杂度：O(n)
// 空间复杂度：O(1)
void buildMaxHeap(int nums[], int n, MaxHeap *H) {
    H->data = nums;
    H->heapSize = n;
    H->capacity = n;
    // 从最后一个非叶结点开始下沉操作
    for (int i = n / 2 - 1; i >= 0; i--) {
        MaxHeapSink(H, i);
    }
}