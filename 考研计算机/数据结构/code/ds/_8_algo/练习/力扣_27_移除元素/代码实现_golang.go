// 时间复杂度：O(n)
// 空间复杂度：O(1)
func removeElement(nums []int, val int) int {
    slow, fast := 0, 0
    for fast < len(nums) {
        if nums[fast] != val {
            nums[slow] = nums[fast]
            slow++
        }
        fast++
    }
    return slow
}