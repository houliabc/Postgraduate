#include <stdio.h>

// 简单选择排序
// 时间复杂度：O(n^2)
// 空间复杂度：O(1)
void SelectSort(int nums[], int n) {
    // 每趟将无序区间 [i...n - 1] 中的最小元素和 i 元素进行交换
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (nums[j] < nums[min]) min = j;
        }
        if (min != i) {
            int t = nums[i];
            nums[i] = nums[min];
            nums[min] = t;
        }
    }
}

int main() {
    int nums[8] = {49, 38, 65, 97, 76, 13, 27, 49};
    SelectSort(nums, 8);

    for (int i = 0; i < 8; i++)
        printf("%d, ", nums[i]);
}