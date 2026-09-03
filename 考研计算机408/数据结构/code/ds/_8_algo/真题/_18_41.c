#include <stdbool.h>
#include "HashTable.c"

// 方法一：线性查找
int missSmallestNum(int nums[], int n) {
    // 从 1 到 n + 1
    for (int i = 1; i <= n + 1; i++) {
        // 检查数组 nums 中是否存在正整数 i
        bool exist = false;
        for (int j = 0; i < n; j++) {
            if (nums[j] == i) break;
        }
        // 如果不存在，那么这个 i 就是缺失的最小正整数
        if (!exist) return i;
    }
    return -1; // 这里不会执行到
}

// 方法二：哈希查找
int missSmallestNum(int nums[], int n) {
    // 声明并初始化哈希表
    HashTable table;
    InitHashTable(&table, n);

    // 先将数组 nums 中元素插入到哈希表中，用于高效查找
    for (int i = 0; i < n; i++) {
        if (nums[i] > 0) PutHashTable(&table, nums[i], 1);
    }

    // 从 1 到 n + 1
    for (int i = 1; i <= n + 1; i++) {
        // 如果不存在，那么这个 i 就是缺失的最小正整数
        if (!GetHashTable(&table, i, NULL)) return i;
    }
    return -1; // 这里不会执行到
}

// 方法二：数组来代替哈希表
int missSmallestNum(int nums[], int n) {
    // table[i] = true，表示正整数 i + 1 存在于 nums 中
    bool table[n + 1];

    for (int i = 0; i < n; i++) {
        if (nums[i] >= 1 && nums[i] <= n + 1) 
            table[nums[i] - 1] = true;
    }

    // 从 1 到 n + 1
    for (int i = 1; i <= n + 1; i++) {
        // 如果不存在，那么这个 i 就是缺失的最小正整数
        if (!table[i - 1]) return i;
    }
    return -1; // 这里不会执行到
}

// 方法三：二分查找
int missSmallestNum(int nums[], int n) {
    // 使用快排对数组 nums 进行升序排列
    qucikSort(nums, n);

    // 从 1 到 n + 1
    for (int i = 1; i <= n + 1; i++) { // O(n)
        // 检查数组 nums 中是否存在正整数 i
        bool exist = false;
        int left = 0, right = n - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (nums[i] == i) {
                exist = true;
                break;
            } else if (nums[mid] > i) right = mid - 1;
            else left = mid + 1;
        }
        // 如果不存在，那么这个 i 就是缺失的最小正整数
        if (!exist) return i;
    }
    return -1; // 这里不会执行到
}

// 方法四：排序查找
int missSmallestNum(int nums[], int n) {
    // 使用快排对数组 nums 进行升序排列
    qucikSort(nums, n);

    int missNum = 1; // 从最小正整数 1 开始
    for (int i = 0; i < n; i++) {
        // 当 nums[i] 不在 1 ~ n + 1 范围内，跳过，不用管
        if (nums[i] <= 0 || nums[i] > n + 1) continue;

        // 如果不是第一个元素，并且等于前一个元素，不做任何处理
        if (i != 0 && nums[i] == nums[i - 1]) continue;
        else if (nums[i] == missNum) missNum++; // 不是缺失正整数，那么去检查下一个正整数
        else break;  // missNum 就是缺失的正整数
    }
    return missNum; 
}


