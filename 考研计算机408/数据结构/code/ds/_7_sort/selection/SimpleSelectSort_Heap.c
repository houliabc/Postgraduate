#include <stdio.h>

#include "MinHeap.c"

// 简单选择排序
// 时间复杂度: O(nlogn)
// 空间复杂度: O(n)
void SelectSort(int nums[], int n) {
    MinHeap h;
    InitMinHeap(&h, n);

    for (int i = 0; i < n; i++) MinHeapInsert(&h, nums[i]);

    int minEle;
    for (int i = 0; i < n; i++) {
        // 在 nums[i...n - 1] 中选择最小的元素
        MinHeapDelMin(&h, &minEle);

        nums[i] = minEle;
    }
}

int main() {
    int nums[8] = {49, 38, 65, 97, 76, 13, 27, 49};
    SelectSort(nums, 8);

    for (int i = 0; i < 8; i++)
        printf("%d, ", nums[i]);
}