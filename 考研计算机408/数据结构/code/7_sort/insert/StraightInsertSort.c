#include <stdio.h>

// 直接插入排序
void InsertSort1(int nums[], int n) {
    // [0, i - 1]是有序的，[i，n]是无序的，每次从无序列表中选择一位插入到有序列表里
    for (int i = 1; i < n; i++) {
        int j = i - 1, t = nums[i], insertPos = i;  // 插入位置默认是当前无序列表中第一个位置，表示当前元素比有序列表里最大的元素还要大
        for (; j >= 0; j--) {
            // 找到第一个比t大的（离t最近且大于t的），也就是有比t大的就更新及挪位置
            if (t < nums[j]) {
                nums[j + 1] = nums[j];
                // 记录插入位置
                insertPos = j;
            }
        }
        nums[insertPos] = t;
    }
}

// 直接插入排序
// 时间复杂度：O(n^2)
// 空间复杂度：O(1)
void InsertSort(int nums[], int n) {
    // [0, i - 1]是有序的，[i，n]是无序的，每次从无序列表中选择一位插入到有序列表里
    for (int i = 1; i < n; i++) {
        int j = i, t = nums[i];
        // 顺序查找：从后往前遍历 [0...i - 1] 有序区间中
        // 找到最后一个大于 nums[i] 的元素
        for (; j > 0 && t < nums[j - 1]; j--) {
                nums[j] = nums[j - 1];
        }
        nums[j] = t;
    }
}

int main() {
    int nums[8] = {49, 38, 65, 97, 76, 13, 27, 49};
    InsertSort(nums, 8);

    for (int i = 0; i < 8; i++)
        printf("%d, ", nums[i]);
}