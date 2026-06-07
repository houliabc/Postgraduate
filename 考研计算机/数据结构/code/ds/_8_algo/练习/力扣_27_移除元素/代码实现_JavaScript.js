// 时间复杂度：O(n)
// 空间复杂度：O(1)
var removeElement = function(nums, val) {
    let slow = 0, fast = 0
    while (fast < nums.length) {
        if (nums[fast] != val) {
            nums[slow] = nums[fast]
            slow++
        }
        fast++
    }

    return slow
};