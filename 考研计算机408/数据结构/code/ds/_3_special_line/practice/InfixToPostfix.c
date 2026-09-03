#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CharSqStack.c"

#define MAX_SIZE 100

// 拿到运算符优先级
int precedence(char c) {
    if (c == '+' || c == '-') {
        return 1;
    }
    if (c == '*' || c == '/') {
        return 2;
    }
    return 0;
}

// 中缀表达式转后缀表达式
// infix 是中缀表达式
// postfix 是需要返回的后缀表达式
void infixToPostfix(char *infix, char *postfix) {
    CharSqStack s;
    InitCharStack(&s);

    int j = 0;
    char e;
    
    for (int i = 0; infix[i] != '\0'; i++) {
        if (infix[i] == ' ') continue;
        if (isdigit(infix[i])) {  // 如果是操作数，直接放到后缀表达式
            postfix[j++] = infix[i];
        } else if (infix[i] == '(') {   // 如果是左括号，直接入栈
            PushCharStack(&s, infix[i]);
        } else if (infix[i] == ')') {   // 遇到右括号
            while (GetTopCharStack(&s, &e) && e != '(') { // 栈顶不是左小括号
                postfix[j++] = e;   // 将栈顶运算符加入后缀表达式
                PopCharStack(&s, NULL);
            }
            // 栈顶是左括号，直接出栈
            if (GetTopCharStack(&s, &e) && e == '(') PopCharStack(&s, NULL);
        } else {    // 遇到的是运算符
            // 栈不空、且栈顶不是左小括号、且栈顶运算符优先级大于等于当前运算符
            while (GetTopCharStack(&s, &e) && e != '(' 
                    && precedence(e) >= precedence(infix[i])) {
                postfix[j++] = e;       // 将栈顶运算符加入后缀表达式
                PopCharStack(&s, NULL);
            }
            // 将当前运算符入栈
            PushCharStack(&s, infix[i]);
        }
    }

    // 栈不空的话，将栈中的运算符依次弹出，放到后缀表达式
    while (PopCharStack(&s, &e)) postfix[j++] = e;

    // 添加后缀表达式字符串的结束符
    postfix[j] = '\0';

    DestroyCharStack(&s);
}

int main() {
    char postfix[MAX_SIZE];

    // char *infix = "3 + 4 *  2 -  6";
    char *infix = "3 + 4 * ( 2 - 3 * 3 )";

    infixToPostfix(infix, postfix);
    printf("postfix is: %s\n", postfix);

    return 0;
}    