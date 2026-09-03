// 时间复杂度：O(n)
// 空间复杂度：O(1)
int removeDuplicates(int* nums, int numsSize) {
    int slow = 1, fast = 1;
    while (fast < numsSize) {
        if (nums[fast] != nums[slow - 1]) {
            nums[slow] = nums[fast];
            slow++;
        }
        fast++;
    }
    return slow;
}