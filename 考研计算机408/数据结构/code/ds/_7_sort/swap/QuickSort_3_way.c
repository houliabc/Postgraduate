#include <stdio.h>
#include <stdlib.h>

void swap(int nums[], int i, int j) {
    int tmp = nums[i];
    nums[i] = nums[j];
    nums[j] = tmp;
}

// 三路快排
// 对数组 nums 的区间 [left...right] 进行排序
void quickSort(int nums[], int left, int right) {
    if (left >= right) return;

    // 随机选择分区点并
    int randomIndex = left + rand() % (right - left + 1);
    int pivot = nums[randomIndex];

    int less = left, great = right;
    int i = left;
    while (i <= great) {
        if (nums[i] < pivot) {
            swap(nums, i, less);
            less++;
            i++;
        } else if (nums[i] > pivot) {
            swap(nums, i, great);
            great--;
        } else i++;
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