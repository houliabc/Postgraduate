
# 删除字符串前后的所有空字符
# 时间复杂度：O(n)
# 空间复杂度：O(1)
def trim(s):
    chars = list(s)
    n = len(chars)
    i, j = 0, n - 1

    while i < n and chars[i] == ' ':
        i += 1
    while j >= 0 and chars[j] == ' ':
        j -= 1

    return ''.join(chars[i:j+1])


# 删除字符串中所有的空字符，但是单词之间需要一个空字符隔开
# 时间复杂度：O(n)
# 空间复杂度：O(1)，原地删除空字符
def trim2(s):
    chars = list(s)
    n = len(chars)
    slow, fast = 0, 0

    while fast < n:
        if chars[fast] != ' ' or (fast >= 1 and chars[fast - 1] != ' '):
            chars[slow] = chars[fast]
            slow += 1
        fast += 1

    if slow >= 1 and chars[slow - 1] == ' ':
        slow -= 1

    return ''.join(chars[0:slow])