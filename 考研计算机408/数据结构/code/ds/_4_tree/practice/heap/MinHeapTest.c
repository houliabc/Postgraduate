#include<stdio.h>

#include "MinHeap.c"

int main() {
    int nums[10] = {3, 4, 7, 8, 10, 9, 1, 2, 14, 16};

    MinHeap H;
    buildMinHeap(nums, 10, &H);

    HElemType e;
    extractMin(&H, &e);
    printf("smallest num is: %d\n", e); // 最小值 1

    for (int i = 0; i < 10; i++) {
        printf("%d, ", nums[i]);
    }
    printf("\n");

    MinHeapDelMin(&H, &e);
    printf("smallest num is: %d\n", e); // 最小值 1

    MinHeapInsert(&H, 100);
    extractMin(&H, &e);
    printf("smallest num is: %d\n", e); // 最小值 2

    for (int i = 0; i < 10; i++) {
        printf("%d, ", nums[i]);
    }
    printf("\n");

    return 0;
}