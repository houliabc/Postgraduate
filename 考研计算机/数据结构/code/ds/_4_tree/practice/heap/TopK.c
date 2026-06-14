#include <stdio.h>
#include "MinHeap.c"

// 时间复杂度是 O(nlogk)
// 空间复杂度是 O(k)
void topK(int nums[], int n, int k) {
    // 定义并初始化一个大小为 k 的小根堆
    MinHeap H;
    InitMinHeap(&H, k);

    // 将前 k 个元素放到小顶堆中
    for (int i = 0; i < k; i++) {
        MinHeapInsert(&H, nums[i]);
    }

    // 依次遍历剩下的元素
    HElemType e; 
    for (int i = k; i < n; i++) {
        extractMin(&H, &e);
        if (nums[i] > e) {
            // 删除堆顶最小值
            MinHeapDelMin(&H, NULL);
            // 插入当前元素
            MinHeapInsert(&H, nums[i]);
        }
    }

    // 打印 top k 个元素
    printf("top %d: \n", k);
    while (MinHeapDelMin(&H, &e)) {
        printf("%d, ", e);
    }
    printf("\n");
} 

int main() {
    int nums[10] = {3, 4, 7, 8, 10, 9, 1, 2, 14, 16};

    topK(nums, 10, 4);

    return 0;
}

