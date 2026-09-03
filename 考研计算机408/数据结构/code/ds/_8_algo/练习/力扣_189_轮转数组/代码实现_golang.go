// 方案一：使用额外数组
func rotate1(nums []int, k int)  {
    n := len(nums)
    k = k % n
    newArr := make([]int, n)
    for i := 0; i < n; i++ {
        index := (i + k) % n
        newArr[index] = nums[i]
    }

    for i := 0; i < n; i++ {
        nums[i] = newArr[i]
    }
}

// 方案二：环状替换
func rotate2(nums []int, k int)  {
    n := len(nums)
    k = k % n

    for start, count := 0, 0; count < n; start++ {
        curr, prev := start, nums[start]
        for ok := true; ok; ok = start != curr {
            next := (curr + k) % n
            nums[next], prev = prev, nums[next]
            curr = next
            count++
        }
    }
}

// 方案三：数组旋转
func rotate(nums []int, k int)  {
    n := len(nums)
    k = k % n

    reverse(nums, 0, n - 1)
    reverse(nums, 0, k - 1)
    reverse(nums, k, n - 1)
}

func reverse(nums []int, start int, end int) {
    for start < end {
        nums[start], nums[end] = nums[end], nums[start]
        start++
        end--
    }
}