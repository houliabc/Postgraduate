// 计数排序
func sortColors1(nums []int)  {
    // 1. 计数
    var count = make([]int, 3)
    for _, num := range nums {
        count[num]++
    }

    // 2. 排序
    var k = 0
    for i := 0; i < 3; i++ {
        var iCnt = count[i]
        for j := 1; j <= iCnt; j++ {
            nums[k] = i
            k++
        }
    }
}

// 三路快排分区应用
// 时间复杂度：O(n)
// 空间复杂度：O(1)
func sortColors(nums []int)  {
    var zero, two, i = 0, len(nums) - 1, 0
    for i <= two {
        if nums[i] == 0 {
            nums[i], nums[zero] = nums[zero], nums[i]
            i++
            zero++
        } else if nums[i] == 2 {
            nums[i], nums[two] = nums[two], nums[i]
            two--
        } else {
            i++
        }
    }
}