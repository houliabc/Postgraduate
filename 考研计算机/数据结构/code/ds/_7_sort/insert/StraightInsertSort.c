#include <stdio.h>

// 直接插入排序
void InsertSort1(int nums[], int n) {
    // [0...i - 1] 有序，[i...n - 1] 无序（其中 1 ≤ i < n）
    // 每趟将无序序列中的第一个元素，插入到有序序列中正确的位置
    for (int i = 1; i < n; i++) {
        int insertEle = nums[i];
        // 顺序查找：从后往前遍历 [0...i - 1] 有序区间中
        // 找到最后一个大于 nums[i] 的元素
        int insertPos = i;
        for (int j = i - 1; j >= 0; j--) {
            if (nums[j] > insertEle) {
                insertPos = j;
            }
        }

        // 将区间 [insertPos...i - 1] 往后移动一位
        for (int j = i - 1; j >= insertPos; j--)
            nums[j + 1] = nums[j];

        // 将 nums[i] 插入正确位置
        nums[insertPos] = insertEle;
    }
}

// 直接插入排序
// 时间复杂度：O(n^2)
// 空间复杂度：O(1)
void InsertSort(int nums[], int n) {
    // [0...i - 1] 有序，[i...n - 1] 无序（其中 1 ≤ i < n）
    // 每趟将无序序列中的第一个元素，插入到有序序列中正确的位置
    for (int i = 1; i < n; i++) {
        int insertEle = nums[i];
        // 顺序查找：从后往前遍历 [0...i - 1] 有序区间中
        // 找到最后一个大于 nums[i] 的元素
        int j = i;
        for (; j > 0 && nums[j - 1] > insertEle; j--) {
            nums[j] = nums[j - 1];
        }

        // 将 nums[i] 插入正确位置
        nums[j] = insertEle;
    }
}

int main() {
    int nums[8] = {49, 38, 65, 97, 76, 13, 27, 49};
    InsertSort2(nums, 8);

    for (int i = 0; i < 8; i++)
        printf("%d, ", nums[i]);
}