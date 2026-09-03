func findDisappearedNumbers(nums []int) []int {
    n := len(nums)
    for i := 0; i < n; i++ {
        index := (nums[i] - 1) % n
        nums[index] += n
    }

    res := make([]int, 0)
    for i := 0; i < n; i++ {
        if nums[i] <= n {
            res = append(res, i + 1)
        }
    }

    return res
}