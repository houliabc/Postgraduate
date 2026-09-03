#include <stdio.h>
#include <stdlib.h>

// 时间复杂度：O(n)
// 空间复杂度：O(1)
int maxArea(int* height, int heightSize) {
    int ans = 0;
    int left = 0, right = heightSize - 1;
    while (left < right) {
        int area = (height[left] < height[right] ? height[left] : height[right]) * (right - left);
        ans = (area > ans ? area : ans);
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
int maxArea1(int* height, int heightSize) {
    int ans = 0;
    for (int i = 0; i < heightSize; i++) {
        for (int j = i + 1; j < heightSize; j++) {
            int area = (height[i] < height[j] ? height[i] : height[j]) * (j - i);
            ans = (area > ans ? area : ans);
        }
    }
    return ans;
}