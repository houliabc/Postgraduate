// 数组反转
function reverse(nums) {
    let left = 0, right = nums.length - 1;
    while (left < right) {
        let tmp = nums[left];
        nums[left] = nums[right];
        nums[right] = tmp;

        left++;
        right--;
    }
}

// 验证回文串
function isPalindrome(s) {
    let left = 0, right = s.length - 1;
    while (left < right) {
        if (s[left] !== s[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}