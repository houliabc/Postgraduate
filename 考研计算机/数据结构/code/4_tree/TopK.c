#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "MinHeap.c"

// 表示从含有n个元素的nums数组中选择最大的k个输出（基于小顶堆实现）
void topK(ElemType *nums, int n, int k) {
    // 先将前k个数据插入到小顶堆中，还要先初始化小顶堆
    MinHeap H;
    InitMinHeap(&H, k);

    // 初始化前k个数据
    for (int i = 0; i < k; i++) {       
        MinHeapInsert(&H, nums[i]);
    }

    // 接下来基于小顶堆的特性来维护这个k个元素的小顶堆
    for (int i = k; i < n; i++) {
        // 因为是选择最大的去输出，所以如果新数据比最小（小顶堆第一个）大，则删掉它，并重新加入进去
        if (nums[i] > H.data[0]) {
            MinHeapDelMin(&H, NULL);
            MinHeapInsert(&H, nums[i]);
        }
    }

    // 打印前k大的元素
    for (int i = 0; i < k; i++) {
        ElemType e;
        MinHeapDelMin(&H, &e);
        printf("%d-", e);
    }
}

int main() {
    int nums[10] = {3, 4, 7, 8, 10, 9, 1, 2, 14, 16};

    topK(nums, 10, 4);

    return 0;
}
