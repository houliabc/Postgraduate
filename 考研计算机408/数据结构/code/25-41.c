（1）
初始化正数最大值1，负数最小值0；逆序遍历数组A，若A[i]值为正，则看是否大于当前最大正数，如果大于则更新最大正数，不管大不大于，都更新res[i]为当前最大正数；若A[i]值为负，则同理更新当前最小负数（包括0），同时将res[i]更新为最小负数。重新遍历数组，该数组对应位置的最大值为该位置值*对应res位置的值
（2）
void calMulMax(int A[], int res[], int n) {
    // 初始化最小负数（从0开始）和最大正数
    int left = 0, right = 1;
    for (int i = n-1; i >= 0; i--) {
        if (A[i] > 0) {
            if (A[i] > right)
                // 更新最大正数
                right = A[i];
            res[i] = right;
        }
        if (A[i] <= 0) {
            if (A[i] < left)
                // 更新最小负数
                left = A[i];
            res[i] = left;
        }
    }
    // 再遍历数组，求得每个元素的乘积最大值
    for (int i = 0; i < n; i++) {
        res[i] *= A[i];
    }
}
（3）时间复杂度O（n），空间复杂度O（1）