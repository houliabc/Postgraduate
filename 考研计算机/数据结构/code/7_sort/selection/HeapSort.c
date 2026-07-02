#include <stdio.h>

#include "MaxHeap.c"

// 堆排序
// 时间复杂度: O(nlogn)
// 空间复杂度: O(1)
void HeapSort(int nums[], int n) {
    MaxHeap heap;
    buildMaxHeap(nums, n, &heap);
    for (int i = n - 1; i >= 0; i--) {
        int t = nums[0];  // 0表示大顶堆的最大的元素，即每次能确定一个最大元素放到最后
        nums[0] = nums[i];  // i表示最大位置存放的地方
        nums[i] = t;

        // 实际在heap中不删除，但个数减少，就当做删除了
        heap.heapSize--;

        // 做下沉操作
        MaxHeapSink(&heap, 0);
    }
}

int main() {
    int nums[8] = {49, 38, 65, 97, 76, 13, 27, 49};
    HeapSort(nums, 8);

    for (int i = 0; i < 8; i++)
        printf("%d, ", nums[i]);
}