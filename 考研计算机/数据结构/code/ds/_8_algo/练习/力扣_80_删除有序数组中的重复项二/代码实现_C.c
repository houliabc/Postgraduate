// 时间复杂度：O(n)
// 空间复杂度：O(1)
int removeDuplicates(int* nums, int numsSize) {
    if (numsSize < 2) return numsSize;
    int slow = 2, fast = 2;
    while (fast < numsSize) {
        if (nums[fast] != nums[slow - 2]) {
            nums[slow] = nums[fast];
            slow++;
        }
        fast++;
    }
    return slow;
}