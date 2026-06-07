#include <ctype.h>
#include <stdio.h>

#include "../SqStack.c"

// 执行运算
int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                printf("Error: Division by zero\n");
                exit(EXIT_FAILURE);
            }
            return a / b;
    }
    return 0;
}

// 计算后缀表达式的值
// 时间复杂度：O(n)，n 是后缀表达式的长度
// 空间复杂度：O(n)
int EvaluatePostfixExp(char *exp) {
    SqStack numStack;
    InitStack(&numStack);

    SElemtype val1, val2;

    for (int i = 0; exp[i] != '\0'; i++) {
        if (exp[i] == ' ') continue;
        if (isdigit(exp[i])) { // 如果是操作数，则入操作数栈
            // 数字字符减去 '0' 得到这个数字字符对应的整数，比如 '9' - '0' = 9，
            // 其实就是将字符 '9' 的 assci 码减去字符 '0' 的 assci 码，这两个字符的 assci 码相差 9
            Push(&numStack, exp[i] - '0'); 
        } else { // 如果是运算符
            char op = exp[i];

            // 弹出栈顶的两个元素
            // 注意顺序，第一个栈顶元素作为 val2，第二个栈顶元素作为 val1
            Pop(&numStack, &val2);
            Pop(&numStack, &val1);

            // 然后将两个操作数进行运算，结果压入栈中
            Push(&numStack, applyOp(val1, val2, op));
        }
    }

    // 操作数栈的栈顶元素就是结果，返回即可
    GetTop(&numStack, &val1);

    DestroyStack(&numStack);
    
    return val1;
}

int main() {
    char *exp = "3 4 2 3 - * + 6 2 / - ";

    int res = EvaluatePostfixExp(exp);
    printf("res is: %d\n", res);

    return 0;
}    