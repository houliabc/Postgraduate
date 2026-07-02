#include <stdio.h>
#include "MinHeap.c"

// 简单选择排序
// 时间复杂度: O(nlogn)
// 空间复杂度: O(n)
void SelectSort(int nums[], int n) {
    // 基于小顶堆来优化简单选择排序
    MinHeap heap;
    InitMinHeap(&heap, n);
    for (int i = 0; i < n; i++) {
        MinHeapInsert(&heap, nums[i]);
    }
    for (int i = 0; i < n; i++) {
        HElemType min;
        MinHeapDelMin(&heap, &min);
        nums[i] = min;
    }
    DestoryMinHeap(&heap);
}

int main() {
    int nums[8] = {49, 38, 65, 97, 76, 13, 27, 49};
    SelectSort(nums, 8);

    for (int i = 0; i < 8; i++)
        printf("%d, ", nums[i]);
}