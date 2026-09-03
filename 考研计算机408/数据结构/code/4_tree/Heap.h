#ifndef HEAP_H
#define HEAP_H

typedef int ElemType;

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

#endif