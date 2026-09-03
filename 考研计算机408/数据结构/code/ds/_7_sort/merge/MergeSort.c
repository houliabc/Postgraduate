#include <stdio.h>

// 二路合并操作
// 将数组 nums 的区间 [left...mid] 和 [mid + 1, right] 进行二路合并
// tmp 是已经创建好的长度为 n 的临时数组
void Merge(int nums[], int tmp[], int left, int mid, int right) {
    // 拷贝区间元素到临时数组
    for (int k = left; k <= right; k++) {
        tmp[k] = nums[k];
    }

    int i = left, j = mid + 1;
    for (int k = left; k <= right; k++) {
        if (i > mid)              nums[k] = tmp[j++];
        else if (j > right)       nums[k] = tmp[i++];
        else if (tmp[i] > tmp[j]) nums[k] = tmp[j++];
        else                      nums[k] = tmp[i++];
    }
}

// 对数组 nums 的区间 [left...right] 进行归并排序
void MSort(int nums[], int tmp[], int left, int right) {
    if (left == right) return;

    int mid = (left + right) / 2;

    MSort(nums, tmp, left, mid);
    MSort(nums, tmp, mid + 1, right);

    Merge(nums, tmp, left, mid, right);
}

// 时间复杂度：O(nlogn)
// 空间复杂度：O(n)
void MergeSort(int nums[], int n) {
    int tmp[n];
    MSort(nums, tmp, 0, n - 1);
}

int main() {
    int nums[8] = {49, 38, 65, 97, 76, 13, 27, 49};
    MergeSort(nums, 8);

    for (int i = 0; i < 8; i++)
        printf("%d, ", nums[i]);
}