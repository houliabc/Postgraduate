package com.laotang.第_1_章_数组和字符串.力扣_26_删除有序数组中的重复项;

public class _26_remove_duplicates_from_sorted_array {
    // 时间复杂度：O(n)
    // 空间复杂度：O(1)
    public int removeDuplicates(int[] nums) {
        int n = nums.length;
        int slow = 1, fast = 1;
        while (fast < n) {
            if (nums[fast] != nums[slow - 1]) {
                nums[slow] = nums[fast];
                slow++;
            }
            fast++;
        }
        return slow;
    }
}
