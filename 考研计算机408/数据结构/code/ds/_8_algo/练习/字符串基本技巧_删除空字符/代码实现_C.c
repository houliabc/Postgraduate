#include <stdlib.h>
#include <string.h>

// 删除字符串前后的所有空字符
// 时间复杂度：O(n)
// 空间复杂度：O(1)
char *trim(char *s) {
    int n = strlen(s);
    int i = 0, j = n - 1;
    while (i < n && s[i] == ' ') i++;
    while (j >= 0 && s[j] == ' ') j--;

    char *result = (char*)malloc((j - i + 2) * sizeof(char));
    strncpy(result, s + i, j - i + 1);
    result[j - i + 1] = '\0';
    return result;
}

// 删除字符串中所有的空字符，但是单词之间需要一个空字符隔开
// 时间复杂度：O(n)
// 空间复杂度：O(1)，原地删除空字符
#include <stdlib.h>
#include <string.h>

char* trim2(char* s) {
    int n = strlen(s);
    int slow = 0, fast = 0;

    while (fast < n) {
        if (s[fast] != ' ' || (fast >= 1 && s[fast - 1] != ' ')) {
            s[slow] = s[fast];
            slow++;
        }
        fast++;
    }

    if (slow >= 1 && s[slow - 1] == ' ') slow--;
    s[slow] = '\0';

    // `strdup()` 函数将字符数组复制到新的内存区域中，并返回该内存区域的指针，以便调用者可以使用该指针来访问新的字符串
    return strdup(s);
}