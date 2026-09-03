class Solution {
public:
    // 时间复杂度：O(n)
    // 空间复杂度：O(1)
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        int slow = 1, fast = 1;
        while (fast < n) {
            if (nums[fast] != nums[slow - 1]) {
                nums[slow] = nums[fast];
                slow++;
            }
            fast++;
        }
        return slow;
    }
};