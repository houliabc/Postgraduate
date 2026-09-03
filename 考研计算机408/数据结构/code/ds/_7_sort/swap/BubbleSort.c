#include <stdio.h>
#include <stdbool.h>

// 冒泡排序
// 时间复杂度：O(n^2)
// 空间复杂度：O(1)
void BubbleSort(int nums[], int n) {
    // 执行 n - 1 趟，每趟将最大的元素放到未排序区间的最后
    for (int round = 1; round <= n - 1; round++) {
        bool hasSwap = false;
        int compareTimes = n - round;
        for (int i = 0; i < compareTimes; i++) {
            if (nums[i] > nums[i + 1]) {
                int tmp = nums[i];
                nums[i] = nums[i + 1];
                nums[i + 1] = tmp;
                hasSwap = true;
            }
        }
        if (!hasSwap) break;
    }
}


int main() {
    int nums[8] = {49, 38, 65, 97, 76, 13, 27, 49};
    BubbleSort(nums, 8);

    for (int i = 0; i < 8; i++)
        printf("%d, ", nums[i]);
}