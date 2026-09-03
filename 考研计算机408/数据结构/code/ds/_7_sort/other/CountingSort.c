#include <stdio.h>

// 时间复杂度：O(max(n,k))
// 空间复杂度：O(k)，如果 k 过于太大的话，导致需要的空间太大了，一般而言 k 不会太大
// 稳定的排序算法
void CountingSort(int nums[], int output[], int n, int k) {
    int counts[k + 1];
    for (int i = 0; i <= k; i++) 
        counts[i] = 0;

    // 统计 nums 数组中，每个元素出现的次数
    for (int i = 0; i < n; i++) 
        counts[nums[i]] += 1;

    // 计算小于等于 nums 数组中每个元素的整数个数
    for (int i = 1; i <= k; i++)
        counts[i] += counts[i - 1];

    // 为了保证排序的稳定性，从右往左遍历 nums
    for (int i = n - 1; i >= 0; i--) {
        // 根据小于等于 nums[i] 的元素个数，将 nums[i] 放到排序后的正确位置上
        output[counts[nums[i]] - 1] = nums[i];
        // 放完一个，相应的 counts 要减 1
        counts[nums[i]]--;
    }
}

int main() {
    int nums[8] = {2, 5, 3, 0, 2, 3, 0, 3};

    int output[8];
    CountingSort(nums, output, 8, 5);

    for (int i = 0; i < 8; i++)
        printf("%d, ", output[i]);
}