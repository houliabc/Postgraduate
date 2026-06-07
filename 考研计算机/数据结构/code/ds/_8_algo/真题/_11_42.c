
// 方法一：合并两个有序序列
int media(int A[], int B[], int L) {
    int C[2 * L];

    int i = 0, j = 0;
    int k = 0;
    while (i < L && j < L) {
        if (A[i] < B[j]) C[k++] = A[i++];
        else C[k++] = B[j++];
    }

    while (i < L) C[k++] = A[i++];
    while (j < L) C[k++] = B[j++];

    return C[L - 1];  // 返回第 L 个元素，即中位数
}


// 方法二：合并 L 个元素
int media(int A[], int B[], int L) {
    int i = 0, j = 0;
    int k = 0;
    while (i < L && j < L) {
        if (A[i] < B[j]) {
            if (k++ == L - 1) return A[i]; // 合并到第 L 个元素
            i++;
        } else {
            if (k++ == L - 1) return B[j]; // 合并到第 L 个元素
            j++;
        }
    }

    while (i < L) {
        if (k++ == L - 1) return A[i]; // 合并到第 L 个元素
        i++;
    }
    while (j < L) {
        if (k++ == L - 1) return B[j]; // 合并到第 L 个元素
        j++;
    }

    return -1;  // 这里不会执行到
}

// 方法三：二分查找
int media(int A[], int B[], int L) {
    int s1 = 0, e1 = L - 1, m1;
    int s2 = 0, e2 = L - 1, m2;

    while (s1 != e1 || s2 != e2) {
        m1 = (s1 + e1) / 2;
        m2 = (s2 + e2) / 2;

        if (A[m1] = B[m2]) return A[m1];
        else if (A[m1] < B[m2]) {
            if ((s1 + m1) % 2 == 0) { // s1 到 m1 区间长度为奇数
                s1 = m1;    // 排除 m1 左边的元素
            } else {    // 偶数
                s1 = m1 + 1; // 排除 m1 左边的元素和 m1 元素本身
            }
            
            e2 = m2;    // 排除 m2 右边的元素
        } else {
            if ((s2 + m2) % 2 == 0) { // s2 到 m2 区间长度为奇数
                s2 = m2;    // 排除 m2 左边的元素
            } else { // 偶数
                s2 = m2 + 1; // 排除 m2 左边的元素和 m2 元素本身
            }
            e1 = m1; // 排除 m1 右边的元素
        }
    }

    // 最后 s1==e1 && s2==e2，那么谁小，谁就是中位数
    if (A[s1] < B[s2]) return A[s1];
    else return B[s2];
}