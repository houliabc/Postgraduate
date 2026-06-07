package com.douma._7_day_排序算法._75;

/**
 * @官方网站 : https://douma.ke.qq.com
 * @微信公众号 : 抖码课堂
 * @官方微信号 : bigdatatang01
 * 抖码算法，让算法学习变的简单有趣
 * @作者 : 老汤
 */
public class _75_sort_colors {
    // 计数排序
    public void sortColors1(int[] nums) {
        // 1. 计数
        int[] count = new int[3];
        for (int num : nums) count[num]++;

        // 2. 排序
        int k = 0;
        for (int i = 0; i < 3; i++) {
            int iCnt = count[i];
            for (int j = 1; j <= iCnt; j++) {
                nums[k++] = i;
            }
        }
    }

    // 三路快排
    public void sortColors2(int[] nums) {
        int zero = 0;
        int two = nums.length - 1;
        int i = 0;
        while (i <= two) {
            if (nums[i] == 0) {
                swap(nums, i, zero);
                i++;
                zero++;
            } else if (nums[i] == 2) {
                swap(nums, i, two);
                two--;
            } else {
                i++;
            }
        }
    }

    private void swap(int[] nums, int i, int j) {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
}
