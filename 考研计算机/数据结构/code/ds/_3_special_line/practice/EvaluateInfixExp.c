#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CharSqStack.c"
#include "../SqStack.c"

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

// 中缀表达式的计算
int EvaluateInfixExp(char *exp) {
    // 运算符栈
    CharSqStack opStack;
    InitCharStack(&opStack);
    // 操作数栈
    SqStack numStack;
    InitStack(&numStack);

    SElemtype val1, val2;
    char op;
    for (int i = 0; exp[i] != '\0'; i++) {
        if (exp[i] == ' ') continue;
        if (isdigit(exp[i])) { // 如果是数字，则入操作数栈
            Push(&numStack, exp[i] - '0');
        } else if (exp[i] == '(') { // 如果是左括号，则入运算符栈
             PushCharStack(&opStack, exp[i]);
        } else if (exp[i] == ')') { // 遇到了右括号
            // 那么就从操作数栈拿出两个操作数，再从运算符栈拿出一个运算符，做计算，结果入操作数栈
            // 直到栈空或者遇到左小括号为止
            while (GetTopCharStack(&opStack, &op) && op != '(') {
                Pop(&numStack, &val2);
                Pop(&numStack, &val1);
                PopCharStack(&opStack, &op);

                Push(&numStack, applyOp(val1, val2, op));
            }

            // 弹出左括号
            if (GetTopCharStack(&opStack, &op) && op == '(') 
                PopCharStack(&opStack, NULL);
        } else {   // 遇到了运算符
            // 如果运算符栈顶的运算符的优先级高于当前运算符，则需要做计算
            while (GetTopCharStack(&opStack, &op) && op != '(' 
                        && precedence(op) >= precedence(exp[i])) {
                Pop(&numStack, &val2);
                Pop(&numStack, &val1);
                PopCharStack(&opStack, &op);

                Push(&numStack, applyOp(val1, val2, op));
            }
            // 将当前运算符入运算符栈
            PushCharStack(&opStack, exp[i]);
        }
    }
    // 如果运算符栈中还有运算符，就要继续做计算
    while (PopCharStack(&opStack, &op)) {
        Pop(&numStack, &val2);
        Pop(&numStack, &val1);
        Push(&numStack, applyOp(val1, val2, op));
    }

    // 操作数栈的栈顶元素就是结果，返回即可
    GetTop(&numStack, &val1);

    DestroyStack(&numStack);
    DestroyCharStack(&opStack);

    return val1;
}

int main() {
    char *exp = "3 + 4 * ( 2 - 3 ) - 6 / 2";

    int res = EvaluateInfixExp(exp);
    printf("res is: %d\n", res);

    return 0;
}    