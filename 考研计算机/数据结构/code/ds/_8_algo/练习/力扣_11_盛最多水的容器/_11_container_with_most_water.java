package com.laotang.第_1_章_数组和字符串.力扣_11_盛最多水的容器;

public class _11_container_with_most_water {

    // 时间复杂度：O(n)
    // 空间复杂度：O(1)
    public int maxArea(int[] height) {
        int ans = 0;
        int left = 0, right = height.length - 1;
        while (left < right) {
            int area = Math.min(height[left], height[right]) * (right - left);
            ans = Math.max(ans, area);
            if (height[left] <= height[right]) {
                left++;
            } else {
                right--;
            }
        }
        return ans;
    }

    // 暴力解法
    // 时间复杂度：O(n^2)
    // 空间复杂度：O(1)
    // 2 <= n <= 10^5
    public int maxArea1(int[] height) {
        int n = height.length;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int area = Math.min(height[i], height[j]) * (j - i);
                ans = Math.max(ans, area);
            }
        }
        return ans;
    }
}
