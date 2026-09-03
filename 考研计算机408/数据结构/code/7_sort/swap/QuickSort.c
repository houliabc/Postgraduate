#include <stdio.h>
#include <stdlib.h>

void swap(int nums[], int i, int j) {
    int tmp = nums[i];
    nums[i] = nums[j];
    nums[j] = tmp;
}

// 对数组 nums 的区间 [left...right] 进行一次分区
int partition(int nums[], int left, int right) {
    // // 取第一个元素作为枢轴
    // int pivot = nums[left];
    // 随机化分区点
    int pivot = left + rand() % (right - left + 1);

    while (left < right) {
        // 找到右边第一个小于枢轴元素的
        while (left < right && nums[right] >= pivot) right--;
        nums[left] = nums[right];
        // 找到左边第一个大于枢轴元素的
        while (left < right && nums[left] <= pivot) left++;
        nums[right] = nums[left];
    }
    // left作为数轴的插入位置，且此位置为最终的位置
    nums[left] = pivot;
    return left;
}

// 对数组 nums 的区间 [left...right] 进行排序
void quickSort(int nums[], int left, int right) {
    // 按照二叉树的前序遍历方式来递归的快排
    // 设置退出条件
    if (left >= right) return;

    int pivot = partition(nums, left, right);
    quickSort(nums, left, pivot - 1);
    quickSort(nums, pivot + 1, right);
}

int main() {
    int nums[8] = {49, 38, 65, 97, 76, 13, 27, 49};
    quickSort(nums, 0, 7);

    for (int i = 0; i < 8; i++)
        printf("%d, ", nums[i]);
}