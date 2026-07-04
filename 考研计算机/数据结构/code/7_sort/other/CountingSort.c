#include <stdio.h>

// 时间复杂度：O(max(n,k))
// 空间复杂度：O(k)，如果 k 过于太大的话，导致需要的空间太大了，一般而言 k 不会太大
// 稳定的排序算法
void CountingSort(int nums[], int output[], int n, int k) {
    // 计数排序的核心思想是用空间换取时间，通过一个计数数组来统计各元素出现的频率，再以此数组来进行排序的过程（直接选定一个固定的位置放入）
    int count[k + 1];  // 要多一个位置，k是最大的元素值，加上下标0，要多一个位置
    // 注意区分是到k还是n，统计count用k，否则会越界，注意是<=k，因为k是最大元素值，他的下标在元素值+1的位置
    for (int i = 0; i <= k; i++) count[i] = 0;
    // 统计nums就用n
    for (int i = 0; i < n; i++) count[nums[i]]++;

    // 每一个count存放的只是目前等于对应元素值的内容，但小于元素值的前面的内容还没有统计，应该加上去，合起来count[i]存的就是<=i的元素个数
    for (int i = 1; i <= k; i++) {
        count[i] += count[i - 1];
    }

    // 根据计数数组来排序，逆序才能保证算法的稳定性
    for (int i = n - 1; i >= 0 ; i--) {
        output[count[nums[i]] - 1] = nums[i];
        count[nums[i]]--;
    }
}

int main() {
    int nums[8] = {2, 5, 3, 0, 2, 3, 0, 3};

    int output[8];
    CountingSort(nums, output, 8, 5);

    for (int i = 0; i < 8; i++)
        printf("%d, ", output[i]);
}