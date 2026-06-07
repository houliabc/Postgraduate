

// 三路快排 (一趟扫描)
// 时间复杂度：O(n)
// 空间复杂度：O(1)
const sortColors = function(nums) {
    let zero = 0, two = nums.length - 1
    let i = 0
    while (i <= two) {
        if (nums[i] == 0) {
            swap(nums, i, zero)
            i++
            zero++
        } else if (nums[i] == 2) {
            swap(nums, i, two)
            two--
        } else {
            i++
        }
    }
};

const swap = (nums, i, j) => {
    const temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
};

// 计数排序 (两趟扫描)
// 时间复杂度：O(n)
// 空间复杂度：O(1)
const sortColors1 = (nums) => {
    // 1. 计数
    const count = new Array(3).fill(0);
    for (const num of nums) {
        count[num]++;
    }

    // 2. 排序
    let k = 0;
    for (let i = 0; i <= 2; i++) {
        const num = count[i];
        for (let j = 1; j <= num; j++) {
            nums[k++] = i;
        }
    }
}