// 数组反转
func reverse(nums []int) {
    left, right := 0, len(nums) - 1
    for left < right {
        tmp := nums[left]
        nums[left] = nums[right]
        nums[right] = tmp

        left++
        right--
    }
}

// 验证回文串
func isPalindrome(s string) bool {
    left, right := 0, len(s) - 1
    for left < right {
        if s[left] != s[right] {
            return false
        }
        left++
        right--
    }
    return true
}