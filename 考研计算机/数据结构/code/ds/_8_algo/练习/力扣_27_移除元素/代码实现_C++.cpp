class Solution {
public:
    // 时间复杂度：O(n)
    // 空间复杂度：O(1)
    int removeElement(vector<int>& nums, int val) {
        int n = nums.size();
        int slow = 0, fast = 0;
        while (fast < n) {
            if (nums[fast] != val) {
                nums[slow] = nums[fast];
                slow++;
            }
            fast++;
        }
        return slow;
    }
};