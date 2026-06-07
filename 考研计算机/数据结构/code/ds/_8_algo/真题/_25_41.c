


/*
设有两个长度均为 n 的一维整型数组 A 和 res，对数组 A 中的每个元素 A[i]，
计算 A[i] 与 A[j] (0 ≤ i ≤ j ≤ n-1) 乘积的最大值，并将其保存到 res[i] 中。
例如，若 A[] = {1,4,-9,6}，则得到 res[] = {6,24,81,36}。
现给定数组 A，请设计一个时间和空间上尽可能高效的算法 calMulMax，求 res 中各元素的值
*/


void calMulMax_1(int A[], int res[], int n) {
    int tmp, product;
    for (int i = 0; i < n; i++) { // 对于每个 A[i]
        // j 从 i 开始，求 A[i] * A[j] 的最大值
        product = A[i] * A[i];
        for (int j = i + 1; j < n; j++) {
            tmp = A[i] * A[j];
            if (tmp > product) product = tmp;
        }
        res[i] = product;
    }
}


void calMulMax_2(int A[], int res[], int n) {
    int maxNums[n]; // maxNums[i]：存储 A[i...n-1] 之间的最大值
    int minNums[n]; // minNums[i]：存储 A[i...n-1] 之间的最小值

    // A 中的最后一个元素是最大值，也是最小值
    maxNums[n - 1] = A[n - 1];
    minNums[n - 1] = A[n - 1];

    // A 的最后一个元素对应的 res 就等于最后一个元素乘以最后一个元素
    res[n - 1] = A[n - 1] * A[n - 1];

    for (int i = n - 2; i >= 0; i--) {
        // 计算 A[i...n-1] 之间的最大值
        if (A[i] > maxNums[i + 1]) maxNums[i] = A[i];
        else maxNums[i] = maxNums[i + 1];

        // 计算 A[i...n-1] 之间的最小值
        if (A[i] < minNums[i + 1]) minNums[i] = A[i];
        else minNums[i] = minNums[i + 1];

        if (A[i] > 0) res[i] = A[i] * maxNums[i];
        else if (A[i] < 0) res[i] = A[i] * minNums[i];
        else res[i] = 0;
    }
}

// 空间压缩
void calMulMax_3(int A[], int res[], int n) {
    int maxNum = A[n - 1]; // maxNum：存储 A[i...n-1] 之间的最大值
    int minNum = A[n - 1]; // minNum：存储 A[i...n-1] 之间的最小值

    // A 的最后一个元素对应的 res 就等于最后一个元素乘以最后一个元素
    res[n - 1] = A[n - 1] * A[n - 1];

    for (int i = n - 2; i >= 0; i--) {
        // 计算 A[i...n-1] 之间的最大值
        if (A[i] > maxNum) maxNum = A[i];

        // 计算 A[i...n-1] 之间的最小值
        if (A[i] < minNum) minNum = A[i];

        if (A[i] > 0) res[i] = A[i] * maxNum;
        else if (A[i] < 0) res[i] = A[i] * minNum;
        else res[i] = 0;
    }
}

/*
今天更新了 3 道顺序表相关的真题算法题总结，分别是：

2011 年第 42 题：合并两个升序序列（暴力解法）→ 合并 L 个元素 → 二分查找解法

2020 年第 41 题：暴力枚举 → 缩小查找空间（利用排序的特点）

2025 年第 41 题：暴力解法 → 预处理（动态规划思想）→ 空间压缩

每道题都循序渐进，从最容易的暴力解法，一步一步优化，道最优解，每一种实现都能得到相应的分数

以上内容都放在对应真题的解析中了

如果今年遇到的是顺序表的算法题的，必定是会有很容易想到的暴力解法的，而且用暴力解法，得到的分数也不会太低，大家加油
*/