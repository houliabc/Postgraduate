/**
 * @param {string} s
 * @return {string}
 */
var reverseWords = function(s) {
    s = trim(s)
    chars = s.split('')
    reverse(chars, 0, chars.length - 1)
    reverseEachWord(chars)
    return chars.join('')
};


function reverseEachWord(chars) {

    let n = chars.length;
    let slow = 0, fast = 0;

    while (fast < n) {
        while (fast < n && chars[fast] != ' ') fast++;
        reverse(chars, slow, fast - 1);
        fast++;
        slow = fast;
    }
}

function reverse(chars, left, right) {
    while (left < right) {
        [chars[left], chars[right]] = [chars[right], chars[left]]
        left++
        right--
    }
}

// 删除字符串中所有的空字符，但是单词之间需要一个空字符隔开
// 时间复杂度：O(n)
// 空间复杂度：O(1)，原地删除空字符
function trim(s) {
    let chars = s.split('');
    let n = chars.length;
    let slow = 0, fast = 0;

    while (fast < n) {
        if (chars[fast] !== ' ' || (fast >= 1 && chars[fast - 1] !== ' ')) {
            chars[slow] = chars[fast];
            slow++;
        }
        fast++;
    }

    if (slow >= 1 && chars[slow - 1] == ' ') slow--;

    chars.length = slow;
    return chars.join('');
}