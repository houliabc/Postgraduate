
// 暴力解法
// 时间复杂度：O(n^2)
// 空间复杂度：O(n)
int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int* output = (int*)malloc(sizeof(int) * numsSize);

    for (int i = 0; i < numsSize; i++) {
        // 求左边数的乘积
        int leftProduct = 1;
        for (int j = 0; j < i; j++) {
            leftProduct *= nums[j];
        }
        // 求右边数的乘积
        int rightProduct = 1;
        for (int j = i + 1; j < numsSize; j++) {
            rightProduct *= nums[j];
        }
        // 将左边和右边乘积再相乘
        output[i] = leftProduct * rightProduct;
    }

    return output;
}

// 优化 1：空间换时间
// 时间复杂度：O(n)
// 空间复杂度：O(n)
int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int* output = (int*)malloc(sizeof(int) * numsSize);

    int* leftProducts = (int*)malloc(sizeof(int) * numsSize);
    leftProducts[0] = 1;
    for (int i = 1; i < numsSize; i++) {
        leftProducts[i] = leftProducts[i - 1] * nums[i - 1];
    }

    int* rightProducts = (int*)malloc(sizeof(int) * numsSize);
    rightProducts[numsSize - 1] = 1;
    for (int i = numsSize - 2; i >= 0; i--) {
        rightProducts[i] = rightProducts[i + 1] * nums[i + 1];
    }

    for (int i = 0; i < numsSize; i++) {
        output[i] = leftProducts[i] * rightProducts[i];
    }

    free(leftProducts);
    free(rightProducts);
    return output;
}

// 继续优化，减少空间
// 时间复杂度：O(n)
// 空间复杂度：O(n)
int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int* output = (int*)malloc(sizeof(int) * numsSize);

    // 先将每个元素的左边全部元素的乘积存储在 output 中
    output[0] = 1;
    for (int i = 1; i < numsSize; i++) {
        output[i] = output[i - 1] * nums[i - 1];
    }

    // 每个元素的右边所有元素的乘积存储在一个变量中
    int rightProduct = 1;
    for (int i = numsSize - 1; i >= 0; i--) {
        // 对于索引 i，左边的乘积为 output[i]，右边的乘积为 rightProduct
        output[i] = output[i] * rightProduct;
        // 更新右边乘积
        rightProduct = rightProduct * nums[i];
    }

    return output;
}