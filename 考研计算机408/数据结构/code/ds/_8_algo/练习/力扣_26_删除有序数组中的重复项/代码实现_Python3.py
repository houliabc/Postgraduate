class Solution:
    # 时间复杂度：O(n)
    # 空间复杂度：O(1)
    def removeDuplicates(self, nums: List[int]) -> int:
        slow, fast = 1, 1
        while fast < len(nums):
            if nums[fast] != nums[slow - 1]:
                nums[slow] = nums[fast]
                slow += 1
            fast += 1

        return slow