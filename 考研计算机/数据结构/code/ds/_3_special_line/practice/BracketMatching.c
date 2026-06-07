#include "CharSqStack.c"

// 括号匹配
// 时间复杂度为 O(n)
// 空间复杂度为 O(n)
bool isMatch(char *s, int length) {
    CharSqStack stack;
    InitCharStack(&stack);

    char top;
    for (int i = 0; i < length; i++) {
        char c = s[i]; 
        if (c == '(' || c == '{') {  // 左括号，直接入栈
            PushCharStack(&stack, c);
        } else { // 遇到右括号
            // 栈内没有与之对应的左括号，直接匹配失败
            if (CharStackEmpty(&stack)) return false;

            PopCharStack(&stack, &top);
            if (c == ')' && top != '(') return false;
            if (c == '}' && top != '{') return false;
        }
    }

    bool matched = CharStackEmpty(&stack);
    DestroyCharStack(&stack);
    return matched;
}

int main() {
    bool res = isMatch("({}){}", 6);

    printf("res = %d\n", res);
    return 0;
}