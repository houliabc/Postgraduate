#include <stdio.h>
#include <stdbool.h>

// 冒泡排序
// 时间复杂度：O(n^2)
// 空间复杂度：O(1)
void BubbleSort(int nums[], int n) {
    // 执行 n - 1 趟，每趟将最大的元素放到未排序区间的最后
    for (int i = 0; i < n - 1; i++) {
        // 用于提前推出冒泡排序
        bool flag = false;
        // 每一趟的比较次数从n-1一直到1
        for (int j = 1; j < n - i; j++) {  // 从前往后冒泡
            if (nums[j - 1] > nums[j]) {
                int t = nums[j];
                nums[j] = nums[j - 1];
                nums[j - 1] = t;
                flag = true;
            }
        }
        // 表示这一趟没有交换，则已有序
        if (!flag)
            return;
    }
}


int main() {
    int nums[8] = {49, 38, 65, 97, 76, 13, 27, 49};
    BubbleSort(nums, 8);

    for (int i = 0; i < 8; i++)
        printf("%d, ", nums[i]);
}