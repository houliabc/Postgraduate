#include <stdio.h>

// 折半插入排序
void BInsertSort(int nums[], int n) {
    // [0...i - 1] 有序，[i...n - 1] 无序（其中 1 ≤ i < n）
    // 每趟将无序序列中的第一个元素，插入到有序序列中正确的位置
    for (int i = 1; i < n; i++) {
        int insertEle = nums[i];
        // 折半查找
        // 从 [0...i - 1] 有序序列中，找到第一个大于 nums[i] 的元素
        int insertPos = i;
        int low = 0, high = i - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (nums[mid] > insertEle) { 
                insertPos = mid;
                high = mid - 1;
            } else low = mid + 1;
        }

        // 将区间 [insertPos...i - 1] 往后移动一位
        for (int j = i - 1; j >= insertPos; j--)
            nums[j + 1] = nums[j];

        // 将 nums[i] 插入正确位置
        nums[insertPos] = insertEle;
    }
}


int main() {
    int nums[8] = {49, 38, 65, 97, 76, 13, 27, 49};
    BInsertSort(nums, 8);

    for (int i = 0; i < 8; i++)
        printf("%d, ", nums[i]);
}