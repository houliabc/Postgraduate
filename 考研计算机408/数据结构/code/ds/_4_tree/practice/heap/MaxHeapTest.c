#include<stdio.h>

#include "MaxHeap.c"

int main() {
    int nums[10] = {3, 4, 7, 8, 10, 9, 1, 2, 14, 16};

    MaxHeap H;
    buildMaxHeap(nums, 10, &H);

    HElemType e;
    extractMax(&H, &e);
    printf("largest num is: %d\n", e); // 最大值 16

    for (int i = 0; i < 10; i++) {
        printf("%d, ", nums[i]);
    }
    printf("\n");

    MaxHeapDelMax(&H, &e);
    printf("largest num is: %d\n", e); // 最大值 16

    MaxHeapInsert(&H, 100);
    extractMax(&H, &e);
    printf("largest num is: %d\n", e);  // 最大值 100

    for (int i = 0; i < 10; i++) {
        printf("%d, ", nums[i]);
    }
    printf("\n");

    return 0;
}