package com.laotang.第_1_章_数组和字符串.力扣_80_删除有序数组中的重复项二;

public class _80_remove_duplicates_from_sorted_array_ii {
    // 时间复杂度：O(n)
    // 空间复杂度：O(1)
    public int removeDuplicates(int[] nums) {
        int n = nums.length;
        int slow = 2, fast = 2;
        while (fast < n) {
            if (nums[fast] != nums[slow - 2]) {
                nums[slow] = nums[fast];
                slow++;
            }
            fast++;
        }
        return slow;
    }
}
