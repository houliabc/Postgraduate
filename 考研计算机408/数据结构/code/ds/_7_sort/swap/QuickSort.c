#include <stdio.h>
#include <stdlib.h>

void swap(int nums[], int i, int j) {
    int tmp = nums[i];
    nums[i] = nums[j];
    nums[j] = tmp;
}

// 对数组 nums 的区间 [left...right] 进行一次分区
int partition(int nums[], int left, int right) {
    // 随机化分区点
    int randomIndex = left + rand() % (right - left + 1);
    swap(nums, left, randomIndex);

    int v = nums[left];             // 先记住分区点元素

    while (left < right) { // 从数组的两端交替的往中间遍历
        // 从右往左，找到第一个小于分区点的元素
        while (left < right && nums[right] >= v) right--;
        // 将小于分区点的元素移动到左边
        nums[left] = nums[right];
        // 从左往右，找到第一个大于分区点的元素
        while (left < right && nums[left] <= v) left++;
        // 将大于分区点的元素移动到有边
        nums[right] = nums[left];
    }

    // 将分区点放到排序后的正确位置
    nums[left] = v;

    // 返回分区点的下标
    return left;
}

// 对数组 nums 的区间 [left...right] 进行排序
void quickSort(int nums[], int left, int right) {
    if (left >= right) return;

    int j = partition(nums, left, right);

    quickSort(nums, left, j - 1);
    quickSort(nums, j + 1, right);
}

int main() {
    int nums[8] = {49, 38, 65, 97, 76, 13, 27, 49};
    quickSort(nums, 0, 7);

    for (int i = 0; i < 8; i++)
        printf("%d, ", nums[i]);
}