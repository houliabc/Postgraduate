func partition(nums []int) {
    n := len(nums)
    pivot := nums[n-1]

    slow, fast := 0, 0
    for fast < n-1 {
        if nums[fast] < pivot {
            swap(nums, slow, fast)
            slow++
        }
        fast++
    }
    swap(nums, slow, fast)
}

func swap(nums []int, i int, j int) {
    tmp := nums[i]
    nums[i] = nums[j]
    nums[j] = tmp
}