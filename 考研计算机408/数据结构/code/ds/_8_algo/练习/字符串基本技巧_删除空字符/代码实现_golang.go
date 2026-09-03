
// 删除字符串前后的所有空字符
// 时间复杂度：O(n)
// 空间复杂度：O(1)
func trim(s string) string {
    chars := []rune(s)
    n := len(chars)
    i, j := 0, n-1

    for ; i < n && chars[i] == ' '; i++ {}
    for ; j >= 0 && chars[j] == ' '; j-- {}

    return string(chars[i : j + 1])
}

// 删除字符串中所有的空字符，但是单词之间需要一个空字符隔开
// 时间复杂度：O(n)
// 空间复杂度：O(1)，原地删除空字符
func trim2(s string) string {
    chars := []rune(s)
    n := len(chars)
    slow, fast := 0, 0

    for fast < n {
        if chars[fast] != ' ' || (fast >= 1 && chars[fast - 1] != ' ') {
            chars[slow] = chars[fast]
            slow++
        }
        fast++
    }

    if slow >= 1 && chars[slow - 1] == ' ' {
        slow--
    }

    return string(chars[0:slow])
}