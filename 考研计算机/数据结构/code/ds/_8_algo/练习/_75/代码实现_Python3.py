from typing import List


class Solution:
    # 计数排序 (两趟扫描)
    # 时间复杂度：O(n)
    # 空间复杂度：O(1)
    def sortColors1(self, nums: List[int]) -> None:
        # 1. 计数
        count = [0] * 3
        for num in nums:
            count[num] += 1

        # 2. 排序
        k = 0
        for i in range(3):
            num = count[i]
            for j in range(1, num + 1):
                nums[k] = i
                k += 1

    # 三路快排 (一趟扫描)
    # 时间复杂度：O(n)
    # 空间复杂度：O(1)
    def sortColors(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        zero, two, i = 0, len(nums) - 1, 0
        while i <= two:
            if nums[i] == 0:
                nums[i], nums[zero] = nums[zero], nums[i]
                i, zero = i + 1, zero + 1
            elif nums[i] == 2:
                nums[i], nums[two] = nums[two], nums[i]
                two -= 1
            else: i = i + 1