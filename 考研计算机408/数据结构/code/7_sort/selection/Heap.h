#ifndef HEAP_H
#define HEAP_H

typedef int HElemType;

typedef struct {  
    HElemType *data;  // 存储堆元素的数组
    int capacity;     // 堆容量
    int heapSize;     // 堆大小
} MaxHeap, MinHeap;

// 交换两个元素的值
void swap(HElemType *a, HElemType *b) {
    HElemType temp = *a;
    *a = *b;
    *b = temp;
}

#endif