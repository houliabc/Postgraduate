// 双指针
func maxArea(height []int) int {
    ans, left, right := 0, 0, len(height) - 1
    for left < right {
        area := (right - left) * min(height[left], height[right])
        ans = max(ans, area)
        if height[left] <= height[right] {
            left++
        } else {
            right--
        }
    }
    return ans
}

// 暴力解法
func maxArea1(height []int) int {
    n := len(height)
    ans := 0
    for i := 0; i < n; i++ {
        for j := i + 1; j < n; j++ {
            area := (j - i) * min(height[i], height[j])
            ans = max(ans, area)
        }
    }
    return ans
}

func min(x, y int) int {
    if x < y {
        return x
    }
    return y
}

func max(x, y int) int {
    if x > y {
        return x
    }
    return y
}