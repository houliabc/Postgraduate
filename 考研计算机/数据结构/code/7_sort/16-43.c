思路，不计入答案：“|n1-n2|最小意味着左右区间大小相近，最多差1
[S1-S2]最大意味着一边存放最小的，另一边存放最大的
由此可得，大致的思想就是排序后划分区间？————我想着是用快排或者二路归并”
答：
（1）按照快速排序的思想将集合A进行升序排序，之后按其中间元素进行划分，分配到另外的两个数组A1和A2中。其中这样的划分能保证|n1-n2|最小以及[S1-S2]最大
（2）
int partition(int A[], int low, int high) {
    int pivot = A[0];  // 将第一个元素作为枢轴
    while (low < high) {
        while (low < high && A[high] >= pivot) high--;
        // 找到了高位的第一个小于数轴的元素，挪至左边
        A[low] = A[high];
        while (low < high && A[low] <= pivot) low++;
        // 找到了低位的第一个大于数轴的元素，挪至右边
        A[high] = A[low];
    }
    // 将枢轴放入正确的最终位置上
    A[low] = pivot;
    return low;
}
void fastSort(int A[], int low, int high) {
    // 递归推出条件
    if (low < high) return;
    int pivot = partition(A, low, high);
    // 快排枢轴左边
    fastSort(A, 0, pivot);
    // 快排枢轴右边
    fastSort(A, pivot + 1, high);;
}
void split(int A[], int n, int A1[], int A2[]) {
    //调用快速排序
    fastSort(A, 0, n - 1);
    // 对排好序的数组A进行划分
    //计算左边区间的个数
    int mid = n / 2;
    for (int i = 0; i < mid; i++) {
        A1[i] = A[i];
    }
    for (int i = 0; i < n - mid; i++) {
        A2[i] = A[i + mid];
    }
}
（3）
平均时间复杂度为O(nlogn)
平均空间复杂度为O(logn)