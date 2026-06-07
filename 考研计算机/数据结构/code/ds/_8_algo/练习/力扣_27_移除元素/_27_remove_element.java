package com.laotang.第_1_章_数组和字符串.力扣_27_移除元素;

public class _27_remove_element {
    // 时间复杂度：O(n)
    // 空间复杂度：O(1)
    public int removeElement(int[] nums, int val) {
        int n = nums.length;
        int left = 0, right = n - 1;
        while (left <= right) {
            if (nums[left] == val) {
                nums[left] = nums[right];
                right--;
            } else {
                left++;
            }
        }
        return left;
    }
}
