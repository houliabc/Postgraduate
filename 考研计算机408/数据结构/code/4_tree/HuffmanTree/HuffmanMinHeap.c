#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct {
    // 权值
    int weight;
    // 下标
    int i;
} ElemType;

typedef struct {  
    ElemType *data;  // 存储堆元素的数组
    int capacity;     // 堆容量
    int heapSize;     // 堆大小
} MaxHeap, MinHeap;

// 交换两个元素的值
void swap(ElemType *a, ElemType *b) {
    ElemType temp = *a;
    *a = *b;
    *b = temp;
}

// 堆的初始化
void InitMinHeap(MinHeap *H, int n) {
    H->data = (ElemType*)malloc(sizeof(ElemType) * n);
    H->capacity = n;
    H->heapSize = 0;
}

// 堆的销毁
void DestoryMinHeap(MinHeap *H) {
    if (H->data)
        free(H->data);
}

// 堆判空操作
// 时间复杂度：O(1)
bool MinHeapEmpty(MinHeap *H) {
    return H->heapSize == 0;
}

// 查询最小元素
// 时间复杂度：O(1)
bool extractMin(MinHeap *H, ElemType *e) {
    if (MinHeapEmpty(H))
        return false;
    *e = H->data[0];
    return true;
}

// 往堆中插入元素 e
// 时间复杂度：O(logn)
bool MinHeapInsert(MinHeap *H, ElemType e) {
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
        if (H->data[parent].weight <= H->data[k].weight)
            break;
        
        // 否则就交换，然后进行下一轮
        swap(&H->data[parent], &H->data[k]);
        k = parent;
    }
    return true;
}

// 将下标为 k 的结点做下沉操作
void MinHeapSink(MinHeap *H, int k) {
    int smallest, right;
    while (k * 2 + 1 < H->heapSize) {
        smallest = k * 2 + 1;
        right = k * 2 + 2;
        // 选择子元素最小的
        if (right < H->heapSize && H->data[right].weight < H->data[smallest].weight)
            smallest = right;
        
        // 当前已经符合小顶堆的定义
        if (H->data[k].weight <= H->data[smallest].weight) break;

        swap(&H->data[k], &H->data[smallest]);
        k = smallest;
    }
}

// 删除堆顶最小元素
// 时间复杂度：O(logn)
bool MinHeapDelMin(MinHeap *H, ElemType *e) {
    // TODO: 删除堆顶，返回元素值
    // 先判断是否空
    if (MinHeapEmpty(H))
        return false;
    if (e)
        *e = H->data[0];
    // 将最后一个元素替换当前最小值
    H->data[0] = H->data[H->heapSize - 1];
    H->heapSize--;

    MinHeapSink(H, 0);
    return true;
}