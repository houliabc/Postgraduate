#include <stdio.h>

// 对长度为 n 的数组 nums 进行 h 有序排列
void ShellInsert(int nums[], int n, int h) {
    // 每一趟，进行 h 轮的直接插入排序
    for (int k = 0; k < h; k++) {
        // i = k + 1 同个效果，间隔是h
        for (int i = k + h; i < n; i+=h) {
            int j = i, t = nums[i];
            // 顺序查找：从后往前遍历 [0...i - 1] 有序区间中
            // 找到最后一个大于 nums[i] 的元素
            for (; j >= h && t < nums[j - h]; j -= h) {
                    nums[j] = nums[j - h];
            }
            nums[j] = t;
        }
    }
}

void ShellSort(int nums[], int n, int dt[], int t) {
    // 执行完一个间隔的排序，就是一趟
    for (int i = 0; i < t; i++) 
        ShellInsert(nums, n, dt[i]);
}

int main() {
    int nums[8] = {49, 38, 65, 97, 76, 13, 27, 49};

    int dt[3] = {5, 3, 1};

    ShellSort(nums, 8, dt, 3);

    for (int i = 0; i < 8; i++)
        printf("%d, ", nums[i]);
}