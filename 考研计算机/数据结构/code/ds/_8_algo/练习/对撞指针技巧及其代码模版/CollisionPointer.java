package com.laotang.第_1_章_数组和字符串.对撞指针技巧及其代码模版;

public class CollisionPointer {

    // 数组反转
    public void reverse(int[] nums) {
        int left = 0, right = nums.length - 1;
        while (left < right) {
            int tmp = nums[left];
            nums[left] = nums[right];
            nums[right] = tmp;

            left++;
            right--;
        }
    }
}
