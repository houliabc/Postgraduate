# 时间复杂度：O(n)
# 空间复杂度：O(1)
def removeElement1(self, nums: List[int], val: int) -> int:
    slow = fast = 0
    while fast < len(nums):
        if nums[fast] != val:
            nums[slow] = nums[fast]
            slow += 1
        fast += 1

    return slow