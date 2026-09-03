// 暴力解法
// O(n^2) --> 超时
func productExceptSelf1(nums []int) []int {
    n := len(nums)
    output := make([]int, n)

    for i := 0; i < n; i++ {
        // 求左边数的乘积
        leftProduct := 1
        for j := 0; j < i; j++ {
            leftProduct *= nums[j]
        }
        // 求右边数的乘积
        rightProduct := 1
        for j := i + 1; j < n; j++ {
            rightProduct *= nums[j]
        }
        // 将左边和右边乘积再相乘
        output[i] = leftProduct * rightProduct
    }

    return output
}

// 优化：空间换时间
// 时间复杂度：O(n)
// 空间复杂度：O(n)
func productExceptSelf2(nums []int) []int {
    n := len(nums)

    // leftProducts[i] 表示索引 i 左侧所有元素的乘积
    leftProducts := make([]int, n)
    leftProducts[0] = 1
    for i := 1; i < n; i++ {
        leftProducts[i] = leftProducts[i - 1] * nums[i - 1]
    }

    // rightProducts[i] 为索引 i 右侧所有元素的乘积
    rightProducts := make([]int, n)
    rightProducts[n - 1] = 1
    for i := n - 2; i >= 0; i-- {
        rightProducts[i] = rightProducts[i + 1] * nums[ i + 1]
    }

    output := make([]int, n)
    for i := 0; i < n; i++ {
        output[i] = leftProducts[i] * rightProducts[i]
    }
    return output
}

// 继续优化：减少空间使用
// 时间复杂度：O(n)
// 空间复杂度：O(n)
func productExceptSelf(nums []int) []int {
    n := len(nums)

    // 先将每个元素的左边全部元素的乘积存储在 output 中
    output := make([]int, n)
    output[0] = 1
    for i := 1; i < n; i++ {
        output[i] = output[i - 1] * nums[i - 1]
    }

    // 每个元素的右边所有元素的乘积存储在一个变量中
    rightProduct := 1
    for i := n - 1; i >= 0; i-- { // bug 修复：从右往左遍历，这里应该是 --
        // 对于索引 i，左边的乘积为 output[i]，右边的乘积为 rightProduct
        output[i] = output[i] * rightProduct
        // 更新右边乘积
        rightProduct = rightProduct * nums[i]
    }

    return output
}