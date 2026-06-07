// 时间复杂度：O(n)
// 空间复杂度：O(1)
int removeElement(int* nums, int numsSize, int val) {
    int slow = 0, fast = 0;
    while (fast < numsSize) {
        if (nums[fast] != val) {
            nums[slow] = nums[fast];
            slow++;
        }
        fast++;
    }
    return slow;
}