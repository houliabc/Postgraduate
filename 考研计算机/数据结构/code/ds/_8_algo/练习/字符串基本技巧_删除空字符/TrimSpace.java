package com.laotang.第_1_章_数组和字符串.字符串基本技巧_删除空字符;

public class TrimSpace {

    // 删除字符串前后的所有空字符
    // 时间复杂度：O(n)
    // 空间复杂度：O(1)
    public String trim(String s) {
        char[] chars = s.toCharArray();
        int n = chars.length;
        int i = 0, j = n - 1;

        while (i < n && chars[i] == ' ') i++;
        while (j >= 0 && chars[j] == ' ') j--;

        return new String(chars, i, j - i + 1);
    }

    // 删除字符串中所有的空字符，但是单词之间需要一个空字符隔开
    // 时间复杂度：O(n)
    // 空间复杂度：O(1)，原地删除空字符
    public String trim2(String s) {
        char[] chars = s.toCharArray();
        int n = chars.length;
        int slow = 0, fast = 0;

        while (fast < n) {
            if (chars[fast] != ' ' || (fast >= 1 && chars[fast - 1] != ' ')) {
                chars[slow] = chars[fast];
                slow++;
            }
            fast++;
        }

        if (slow >= 1 && chars[slow - 1] == ' ') slow--;

        return new String(chars, 0, slow);
    }
}
