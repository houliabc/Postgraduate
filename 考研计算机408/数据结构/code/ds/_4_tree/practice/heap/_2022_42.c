

#include "MaxHeap.c"

// 时间复杂度：O(n)
// 空间复杂度：O(1)
void top10(int nums[], int n) {
    // 声明并初始化大小为 10 的大根堆
    MaxHeap H;
    InitMaxHeap(&H, 10);
    // 先将数组 M 中的前 10 个元素依次放入到大根堆 H 中
    for (int i = 0; i < 10; i++) {
        MaxHeapInsert(&H, nums[i]);
    }
    
    HElemType e;
    for (int i = 10; i < n; i++) {
        extractMax(&H, e);
        if (nums[i] < e) { // 如果 num 小于大根堆 H 堆顶的元素
            // 将堆顶元素从堆中删除，然后将 num 放入到大根堆 H 中
            MaxHeapDelMax(&H, NULL);
            MaxHeapInsert(&H, nums[i]);
        }
    }

    // 大根堆中的 10 个元素就是数组 M 中最小的 10 个数
    printf("top 10: ");
    while (MinHeapDelMin(&H, &e)) {
        printf("%d, ", e);
    }
    printf("\n");
}