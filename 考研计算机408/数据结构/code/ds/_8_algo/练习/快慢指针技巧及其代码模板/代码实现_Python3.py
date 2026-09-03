def partition(nums):
    n = len(nums)
    pivot = nums[n - 1]

    slow, fast = 0, 0
    while fast < n - 1:
        if nums[fast] < pivot:
            swap(nums, slow, fast)
            slow += 1
        fast += 1
    swap(nums, slow, fast)

def swap(nums, i, j):
    nums[i], nums[j] = nums[j], nums[i]