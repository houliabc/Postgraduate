（1）定义一个左指针=1，遍历找到数组中值最大且大于0的数，建立对应大小的数组，统计每个正整数是否出现过，且如果值=左指针则左指针+1，且如果+1后的值在count中出现过，则继续加1，输出left的值
（2）
int getMinNumber(int A[], int n) {
    int max = 0, left = 1;
    for (int i = 0; i < n; i++) {
        if (A[i] > max) {
            // 找到第一个大于1的数
            max = A[i];
        }
    }
    int count[max];
    // 遍历数组
    for (int i = 0; i < n; i++) {
        if (A[i] <= 0) continue;
        count[A[i]] = 1;
        if (left == A[i]) {
            left++;
            // 如果右移左指针后的值在统计表出现过，则继续右移
            while (count[left] == 1)
                left++;
        }
    }
    // 如果左指针大于数组长度，输出左指针+1
    if (left > n)
        return n+1;
    else
        return left;
}
（3）
时间复杂度O（n），空间复杂度O（n）