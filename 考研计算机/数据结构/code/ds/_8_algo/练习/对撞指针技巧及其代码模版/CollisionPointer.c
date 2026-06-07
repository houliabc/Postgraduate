// 数组反转
void reverse(int* nums, int numsSize){
    int left = 0, right = numsSize - 1;
    while (left < right) {
        int tmp = nums[left];
        nums[left] = nums[right];
        nums[right] = tmp;

        left++;
        right--;
    }
}

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
// 验证回文串
bool isPalindrome(char* s) {
    int left = 0, right = strlen(s) - 1;
    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}