#include <stdio.h>

// 折半插入排序
void BInsertSort(int nums[], int n) {
    // [0, i - 1]是有序的，[i，n]是无序的，每次从无序列表中选择一位插入到有序列表里
    for (int i = 1; i < n; i++) {
        int insertPos = i, t = nums[i], low = 0, high = i - 1;
        // 将找到第一个大于当前i的元素用折半查找去找
        while (low <= high) {
            int mid = (low + high) / 2;
            if (nums[mid] <= t) low = mid + 1;
            else {
                high = mid - 1;
                insertPos = mid;  // 及时更新插入位置，因为不知道是不是第一个，还是说后面还有
            }
        }
        for (int j = i - 1; j >= 0; j--)
            nums[j + 1] = nums[j];
        nums[insertPos] = t;
    }
}


int main() {
    int nums[8] = {49, 38, 65, 97, 76, 13, 27, 49};
    BInsertSort(nums, 8);

    for (int i = 0; i < 8; i++)
        printf("%d, ", nums[i]);
}