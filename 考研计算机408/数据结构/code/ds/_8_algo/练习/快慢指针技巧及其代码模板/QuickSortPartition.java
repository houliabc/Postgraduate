package com.laotang.第_1_章_数组和字符串.快慢指针技巧及其代码模板;

import java.util.Arrays;

public class QuickSortPartition {
    public void partition(int[] nums) {
        int n = nums.length;
        int pivot = nums[n - 1];

        int slow = 0, fast = 0;
        while (fast < n - 1) {
            if (nums[fast] < pivot) {
                swap(nums, slow, fast);
                slow++;
            }
            fast++;
        }
        swap(nums, slow, fast);
    }

    private void swap(int[] nums, int i, int j) {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }

    public static void main(String[] args) {
        int[] nums = {23, 11, 15, 21, 6, 45, 2, 14};
        new QuickSortPartition().partition(nums);

        System.out.println(Arrays.toString(nums));
    }
}
