/**
 * @param {number[]} nums
 * @return {number}
 */
// 时间复杂度：O(n)
// 空间复杂度：O(1)
var removeDuplicates = function(nums) {
    const n = nums.length;
    var slow = 1, fast = 1
    while (fast < n) {
        if (nums[fast] != nums[slow - 1]) {
            nums[slow] = nums[fast]
            slow++
        }
        fast++
    }
    return slow
};