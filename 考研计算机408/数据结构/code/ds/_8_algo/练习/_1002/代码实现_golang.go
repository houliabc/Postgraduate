// 时间复杂度：O(m*n)，m 表示数组的长度，n 表示每个字符串的平均长度
func commonChars(words []string) []string {
    // 用于存储每个字符在所有字符串中出现的最小次数
    minfreq := [26]int{}

    // 计算第一个单词中每个字符出现的次数
    for _, c := range words[0] {
        minfreq[c - 'a']++
    }

    // 计算每个字符出现的最小次数
    for i := 1; i < len(words); i++ {
        freq := [26]int{}
        for _, c := range words[i] {
            freq[c - 'a']++
        }
        for j := 0; j < 26; j++ {
            minfreq[j] = min(minfreq[j], freq[j])
        }
    }

    // 将字符出现最小次数大于 0 的字符输出到结果中
    res := make([]string, 0)
    for i := 0; i < 26; i++ {
        for j := 0; j < minfreq[i]; j++ {
            res = append(res, string('a' + i))
        }
    }

    return res
}

func min(x, y int) int {
    if x < y {
        return x
    }
    return y
}