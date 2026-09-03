
// 反转数组的区间 [left...right]
void reverse(int *nums, int left, int right) {
    while (left < right) {
        int tmp = nums[left];
        nums[left] = nums[right];
        nums[right] = tmp;

        left++;
        right--;
    }
}

// 使用【反转数组】的操作，来实现旋转数组
// 时间复杂度：O(n)
// 空间复杂度：O(1)
void rotate(int *nums, int n, int p) {
    reverse(nums, 0, n - 1);
    reverse(nums, 0, p - 1);
    reverse(nums, p, n - 1);
}

// 方案一：使用额外数组
// 时间复杂度：O(n)
// 空间复杂度：O(n)
void rotate(int* nums, int numsSize, int k) {
    k %= numsSize;
    int newArr[numsSize];
    for (int i = 0; i < numsSize; i++) {
        int index = (i + k) % numsSize;
        newArr[index] = nums[i];
    }
    for (int i = 0; i < numsSize; i++) {
        nums[i] = newArr[i];
    }
    free(newArr);
}

// 方案二：环状替换
// 时间复杂度：O(n)
// 空间复杂度：O(1)
void rotate(int* nums, int numsSize, int k) {
    k %= numsSize;
    int count = 0;
    for (int start = 0; count < numsSize; start++) {
        int curr = start;
        int prev = nums[start];
        // 循环替换
        do {
            int next = (curr + k) % numsSize;
            int tmp = nums[next];
            nums[next] = prev;
            prev = tmp;

            curr = next;
            count++;
        } while (start != curr);
    }
}