
// Brute-force Matching
// 时间复杂度：O(n * m)
int IndexOf(char *s, int n, char *p, int m) {
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (s[i] == p[j]) {
            i++;
            j++;
        } else {
            // i 回退到本次匹配的开始位置的下一个字符
            i = i - j + 1;
            j = 0;  // j 回退模式串的第一个字符
        }
    }
    if (j == m) return i - m;
    else return -1;
}