#include <stdio.h>
#include <stdlib.h>

void swap(int nums[], int i, int j) {
    int tmp = nums[i];
    nums[i] = nums[j];
    nums[j] = tmp;
}

// 三路快排————无序partition分区了，共五个下标，分为四个分区，[left,less)表示小于pivot，[less,i)表示=pivot，[i,great]表示未处理区域，(great,right]表示大于pivot
// 对数组 nums 的区间 [left...right] 进行排序
void quickSort(int nums[], int left, int right) {
    // 退出条件
    if (left >= right) return;
    // 初始less、great、i
    int less = left, great = right, i = left, pivot = nums[left + rand() % (right - left + 1)];
    // 要求i<=great，也就是处于待处理区域就循环处理
    while (i <= great) {  // ————循环结束后待处理区域完成了，但是左边和右边还没有完成
        // 位于左边，增大less范围，同时交换位置
        if (nums[i] < pivot) {
            swap(nums, i, less);
            less++;
            i++;
        }
        else if (nums[i] > pivot) {
            swap(nums, i, great);
            great--;
        } 
        // 专门针对快排中有大量重复元素的处理
        else  i++;
    }
    quickSort(nums, left, less - 1);
    quickSort(nums, great + 1, right);
}

int main() {
    int nums[8] = {49, 38, 65, 97, 76, 13, 27, 49};
    quickSort(nums, 0, 7);

    for (int i = 0; i < 8; i++)
        printf("%d, ", nums[i]);
}