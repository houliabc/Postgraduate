package com.laotang.第_1_章_数组和字符串.力扣_189_轮转数组;

public class _189_rotate_array {

    // 使用【反转数组】的操作，来实现旋转数组
    // 时间复杂度：O(n)
    // 空间复杂度：O(1)
    public void rotate(int[] nums, int k) {
        int n = nums.length;
        k = k % n;

        reverse(nums, 0, n - 1);
        reverse(nums, 0, k - 1);
        reverse(nums, k, n - 1);
    }

    private void reverse(int[] nums, int left, int right) {
        while (left < right) {
            int tmp = nums[left];
            nums[left] = nums[right];
            nums[right] = tmp;

            left++;
            right--;
        }
    }

    // 方案一：使用额外数组
    // 时间复杂度：O(n)
    // 空间复杂度：O(n)
    public void rotate1(int[] nums, int k) {
        int n = nums.length;
        k = k % n;
        int[] newArr = new int[n];
        for (int i = 0; i < nums.length; i++) {
            int index = (i + k) % n;
            newArr[index] = nums[i];
        }
        System.arraycopy(newArr, 0, nums, 0, n);
    }

    // 方案二：环状替换
    // 时间复杂度：O(n)
    // 空间复杂度：O(1)
    public void rotate2(int[] nums, int k) {
        int n = nums.length;
        k = k % n;
        int count = 0;
        //另一种方式： 这个循环的次数是可以计算得到的，见下面的代码
        for (int start = 0; count < n; start++) {
            int curr = start;
            int prev = nums[start];
            // 循环替换
            do {
                int next = (curr + k) % n;
                int tmp = nums[next];
                nums[next] = prev;
                prev = tmp;

                curr = next;
                count++;
            } while (start != curr);
        }
    }


}
