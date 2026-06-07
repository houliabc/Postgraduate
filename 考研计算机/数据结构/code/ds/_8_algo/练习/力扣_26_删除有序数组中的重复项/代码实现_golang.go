// 时间复杂度：O(n)
// 空间复杂度：O(1)
func removeDuplicates(nums []int) int {
    slow, fast := 1, 1
    for fast < len(nums) {
        if nums[fast] != nums[slow - 1] {
            nums[slow] = nums[fast]
            slow++
        }
        fast++
    }
    return slow
}