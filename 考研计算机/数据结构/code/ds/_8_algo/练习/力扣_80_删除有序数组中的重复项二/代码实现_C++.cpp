class Solution {
public:
    // 时间复杂度：O(n)
    // 空间复杂度：O(1)
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return n;
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
};