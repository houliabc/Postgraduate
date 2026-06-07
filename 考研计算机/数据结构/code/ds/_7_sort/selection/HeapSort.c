#include <stdio.h>

#include "MaxHeap.c"

// 堆排序
// 时间复杂度: O(nlogn)
// 空间复杂度: O(1)
void HeapSort(int nums[], int n) {
    MaxHeap h;

    // 时间复杂度：O(n)
    buildMaxHeap(nums, n, &h);

    // 时间复杂度：O(nlogn)
    for (int i = n - 1; i > 0; i--) {
        int x = nums[0];
        nums[0] = nums[i];
        nums[i] = x;

        h.heapSize--;
        // 时间复杂度：O(logn)
        MaxHeapSink(&h, 0);
    }
}

int main() {
    int nums[8] = {49, 38, 65, 97, 76, 13, 27, 49};
    HeapSort(nums, 8);

    for (int i = 0; i < 8; i++)
        printf("%d, ", nums[i]);
}