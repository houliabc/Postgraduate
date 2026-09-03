#include <stdio.h>

// 二路合并操作
// 将数组 nums 的区间 [left...mid] 和 [mid + 1, right] 进行二路合并
// tmp 是已经创建好的长度为 n 的临时数组
void Merge(int nums[], int tmp[], int left, int mid, int right) {  // 合并的操作
    // 复制nums数组到tmp处
    for (int i = left; i <= right; i++) tmp[i] = nums[i];
    int i = left, j = mid + 1;
    // 对[left,right]范围内进行合并的操作
    for (int k = left; k <= right; k++) {
        if (i > mid) nums[k] = tmp[j++];
        else if (j > right) nums[k] = tmp[i++];
        else if (tmp[i] <= tmp[j]) nums[k] = tmp[i++];
        else nums[k] = tmp[j++];
    }
}

// 对数组 nums 的区间 [left...right] 进行归并排序
void MSort(int nums[], int tmp[], int left, int right) {  //  分割及合并的操作
    // 结束条件：叶子，即left==right
    if (left == right) return;

    // 否则的话按照后续遍历去遍历树
    // 先分割，直至分割到叶子节点的双亲节点
    int mid = (left + right) / 2;
    MSort(nums, tmp, left, mid);
    MSort(nums, tmp, mid + 1, right);

    // 接着对此两个叶子进行合并的过程
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