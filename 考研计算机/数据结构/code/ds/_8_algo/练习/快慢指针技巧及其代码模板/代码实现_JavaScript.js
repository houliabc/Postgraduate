function partition(nums) {
  const n = nums.length;
  const pivot = nums[n - 1];

  let slow = 0,
    fast = 0;
  while (fast < n - 1) {
    if (nums[fast] < pivot) {
      swap(nums, slow, fast);
      slow++;
    }
    fast++;
  }
  swap(nums, slow, fast);
}

function swap(nums, i, j) {
  const tmp = nums[i];
  nums[i] = nums[j];
  nums[j] = tmp;
}