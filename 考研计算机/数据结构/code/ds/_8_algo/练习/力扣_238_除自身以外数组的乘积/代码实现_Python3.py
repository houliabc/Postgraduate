from typing import List


def productExceptSelf(self, nums: List[int]) -> List[int]:
    n = len(nums)
    output = [0] * n
    output[0] = 1
    for i in range(1, n):
        output[i] = output[i - 1] * nums[i - 1]

    right_product = 1;
    for i in range(n - 1, -1, -1):
        output[i] = output[i] * right_product;
        right_product *= nums[i]
    return output
