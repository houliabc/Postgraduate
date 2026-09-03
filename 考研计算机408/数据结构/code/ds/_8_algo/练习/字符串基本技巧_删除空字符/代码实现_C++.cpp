#include <string>
using namespace std;

// 删除字符串前后的所有空字符
// 时间复杂度：O(n)
// 空间复杂度：O(1)
string trim(string s) {
    vector<char> chars(s.begin(), s.end());
    int n = chars.size();
    int i = 0, j = n - 1;

    while (i < n && chars[i] == ' ') i++;
    while (j >= 0 && chars[j] == ' ') j--;

    return string(chars.begin() + i, chars.begin() + j + 1);
}

// 删除字符串中所有的空字符，但是单词之间需要一个空字符隔开
// 时间复杂度：O(n)
// 空间复杂度：O(1)，原地删除空字符
#include <string>
using namespace std;

string trim2(string s) {
    char* chars = &s[0];
    int n = s.size();
    int slow = 0, fast = 0;

    while (fast < n) {
        if (chars[fast] != ' ' || (fast >= 1 && chars[fast - 1] != ' ')) {
            chars[slow] = chars[fast];
            slow++;
        }
        fast++;
    }

    if (slow >= 1 && chars[slow - 1] == ' ') slow--;

    return string(chars, slow);
}

