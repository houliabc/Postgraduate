// 时间复杂度：O(n)
// 空间复杂度：O(1)
func removeDuplicates(nums []int) int {
    if len(nums) <= 2 {
        return len(nums)
    }
    // slow 表示已经处理区域的最后一个位置的下一个位置
    slow, fast := 2, 2
    for fast < len(nums) {
        if nums[fast] != nums[slow - 2] {
            nums[slow] = nums[fast]
            slow++
        }
        fast++
    }
    return slow
}