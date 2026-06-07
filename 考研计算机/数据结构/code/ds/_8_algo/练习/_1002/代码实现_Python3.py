from typing import List


def commonChars(self, A: List[str]) -> List[str]:
    min_freq = [0] * 26
    for c in A[0]:
        min_freq[ord(c) - ord('a')] += 1
    for i in range(1, len(A)):
        freq = [0] * 26
        for c in A[i]:
            freq[ord(c) - ord("a")] += 1
        for j in range(26):
            min_freq[j] = min(min_freq[j], freq[j])

    ans = list()
    for i in range(26):
        ans.extend([chr(i + ord("a"))] * min_freq[i])
    return ans;
