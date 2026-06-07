/**
 * @param {number[]} nums
 * @return {number}
 */
// 时间复杂度：O(n)
// 空间复杂度：O(1)
var removeDuplicates = function(nums) {
    const n = nums.length
    var slow = 2
    var fast = 2
    while (fast < n) {
        if (nums[fast] != nums[slow - 2]) {
            nums[slow] = nums[fast]
            slow++
        }
        fast++
    }
    return slow
};