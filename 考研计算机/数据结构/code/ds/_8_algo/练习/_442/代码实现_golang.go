
// 使用绝对值标记
func findDuplicates1(nums []int) []int {
    res := make([]int, 0)
    for i := 0; i < len(nums); i++ {
        index := abs(nums[i]) - 1
        if nums[index] < 0 {
            res = append(res, abs(nums[i]))
        } else {
            nums[index] = -nums[index]
        }
    }
    return res
}

func abs(n int) int {
    if n < 0 {
        return -n
    }
    return n
}

func findDuplicates(nums []int) []int {
    n := len(nums)
    for i := 0; i < n; i++ {
        index := (nums[i] - 1) % n
        nums[index] += n
    }

    res := make([]int, 0)
    for i := 0; i < len(nums); i++ {
        if nums[i] > 2 * n {
            res = append(res, i + 1)
        }
    }
    return res
}