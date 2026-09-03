
// 方法一：暴力解法
void rotate_1(int R[], int n, int p) {
    int tmp[n];

    for (int i = 0; i < n; i++) {
        // 将元素 R[i] 左移 p 个位置
        int idx = (i - p + n) % n;
        tmp[idx] = R[i];
    }

    // 将循环左移 p 个位置的数组元素拷贝到原数组 R 中
    for (int i = 0; i < n; i++) R[i] = tmp[i];
}

// 方法二：降低空间复杂度
void rotate_2(int R[], int n, int p) {
    int tmp[p];

    // ① 先保存 R 中的前 p 个元素到临时数组
    for (int i = 0; i < p; i++) tmp[i] = R[i];

    // ② 将 R 中后面的 n - p 个元素都左移 p 个位置
    for (int i = p; i < n; i++) {
        // 将元素 R[i] 左移 p 个位置
        int idx = i - p;
        tmp[idx] = R[i];
    }

    // ③ 将临时数组中的 p 个元素放到数组 R 的后面
    for (int i = 0; i < p; i++) R[i + n - p] = tmp[i];
}

// 方法三：再次降低空间复杂度
void rotate_3(int R[], int n, int p) {
    int start = 0;
    for (int count = 0; count < n; start++) {
        int i = start;
        int prev = R[i];
        do {
            // 左移 R[i] 元素
            int next = (i - p + n) % n;

            int tmp = R[next];
            R[next] = prev;
            prev = tmp;

            i = next;
            count++;    // 记录左移元素的个数
        } while (i != start);
    }
}


// 对数组 arr 的区间 [left...right] 的元素进行翻转
void reverse(int arr[], int left, int right) {
    while (left < right) {
        int tmp = arr[left];
        arr[left] = arr[right];
        arr[right] = tmp;

        left++;
        right--;
    }
}

// 方法四：数组翻转
void rotate_3(int R[], int n, int p) {
    // 翻转整个数组 R
    reverse(R, 0, n - 1);
    // 翻转数组 R 的前 n - p 个元素
    reverse(R, 0, n - p - 1);
    // 翻转数组 R 的后 p 个元素
    reverse(R, n - p, n - 1);
}