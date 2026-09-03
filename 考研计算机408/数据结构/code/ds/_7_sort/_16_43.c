#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "MinHeap.c"

// 比较函数用于qsort排序
//  void *a 表示 a 的指针类型是空，也就是不知道 a 指向的位置存储的是什么类型的数据
int compare(const void *a, const void *b) {
    // (int *)a 就是将 a 强转成 int 类型的指针，因为此时，我们知道 a 指向的是 int 类型数据
    // 然后通过 *(int *)a 访问 a 指向的位置的 int 类型的数据
    // 如果返回负数，说明 a 指向的数据小于 b 指向的数据
    // 如果返回正数，说明 a 指向的数据大于 b 指向的数据
    // 如果返回 0，说明 a 指向的数据等于于 b 指向的数据
    return (*(int *)a - *(int *)b);
}

int maxSumDifference1(int A[], int n) {
    // 对数组 A 进行升序排序
    sort(A, n);
    
    // 计算子集A₁的元素和（前n/2个元素）
    int S1 = 0;
    for (int i = 0; i < n/2; i++) {
        S1 += A[i];
    }
    
    // 计算子集A₂的元素和（后n/2个元素）
    int S2 = 0;
    for (int i = n/2; i < n; i++) {
        S2 += A[i];
    }
    
    // 返回两个子集和的差的绝对值
    return abs(S1 - S2);
}

int main() {
    // 示例测试
    int A[] = {3, 1, 4, 2, 5, 7};
    int n = sizeof(A) / sizeof(A[0]);
    
    printf("最大和差: %d\n", maxSumDifference1(A, n));
    
    return 0;
}


// 对数组 nums 的区间 [left...right] 进行一次分区
int partition(int nums[], int left, int right) {
    int randomIndex = left + rand() % (right - left + 1);  // 随机化分区点
    int v = nums[randomIndex];             // 先记住分区点元素
    nums[randomIndex] = nums[left];
    nums[left] = v;

    // 将小于等于 v 的元素放在 v 的左边，大于等于 v 的元素放在 v 的右边
    while (left < right) { 
        while (left < right && nums[right] >= v) right--;
        nums[left] = nums[right];
        while (left < right && nums[left] <= v) left++;
        nums[right] = nums[left];
    }
    nums[left] = v;
    return left;
}

// 将集合 A 划分成两个子集合，其两个集合中的元素相差最小，且两个子集合元素之和相差最大
int maxSumDifference(int A[], int n) {
    // 在数组 A 中查找第 ⌊ n/2 ⌋ 大元素
    int left = 0, right = n - 1;
    // 分区时，如果分区点放在下标 ⌊ n/2 ⌋ - 1 下标位置上，那么这个分区点就是第 ⌊ n/2 ⌋ 大元素
    int k = n / 2 - 1;  
    while (true) {
        // 每次分区，存放在下标 j 的位置的元素，是第 j + 1 大元素
        int j = partition(A, left, right);
        // 分区点放到 k 的位置，那么分区点就是第 ⌊ n/2 ⌋ 大元素，退出循环
        if (j == k) break;
        else if (j < k) left = j + 1;   // 分区点放到 k 的左边，那么分区点小于第 ⌊ n/2 ⌋ 大元素，则去右区间分区
        else right  = j - 1;    // 分区点放到 k 的右边， 那么分区点大于第 ⌊ n/2 ⌋ 大元素，则去左区间分区
    }

    // k 元素就是第 ⌊ n/2 ⌋ 大元素
    // 下标 k，将集合 A，分成符合题目要求的两个子集 [0...k] 和 [k + 1...n - 1]
    int s1 = 0, s2 = 0;
    for (int i = 0; i <= k; i++) s1 += A[i];
    for (int i = k + 1; i < n; i++) s2 += A[i];
    // 返回两个集合所有元素之和的差
    return s2 - s1;
}

int maxSumDifference(int A[], int n) {
    int mid = n / 2;

    MinHeap H;
    InitMinHeap(&H, mid);

    int total = 0;

    // 第一步：将数组 A 中最大的 n/2 个数放在小根堆中
    // 将前 n/2 个元素放到小顶堆中
    for (int i = 0; i < mid; i++) {
        total += A[i];
        MinHeapInsert(&H, A[i]);
    }
    HElemType e; 
    for (int i = mid; i < n; i++) {
        total += A[i];
        extractMin(&H, &e);
        if (A[i] > e) {
            // 删除堆顶最小值
            MinHeapDelMin(&H, NULL);
            // 插入当前元素
            MinHeapInsert(&H, A[i]);
        }
    }

    // 第二步：计算数组 A 中最大的 n/2 个数的和
    int S1 = 0;
    while (MinHeapDelMin(&H, &e)) S1 += e;

    // 返回两个集合所有元素之和的差
    return abs(total - S1 - S1);
}