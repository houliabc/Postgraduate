#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MinHeap.c"

int main() {
    int nums[10] = {3, 4, 7, 8, 10, 9, 1, 2, 14, 16};

    MinHeap H;
    buildMinHeap(nums, 10, &H);

    ElemType e;
    extractMin(&H, &e);
    printf("largest num is: %d\n", e); // 最大值 16

    for (int i = 0; i < 10; i++) {
        printf("%d, ", nums[i]);
    }
    printf("\n");

    MinHeapDelMin(&H, &e);
    printf("largest num is: %d\n", e); // 最大值 16

    MinHeapInsert(&H, 100);
    extractMin(&H, &e);
    printf("largest num is: %d\n", e);  // 最大值 100

    for (int i = 0; i < 10; i++) {
        printf("%d, ", nums[i]);
    }
    printf("\n");

    return 0;
}