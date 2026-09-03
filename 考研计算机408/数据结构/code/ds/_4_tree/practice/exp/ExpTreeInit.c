#include <stdio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../BiTree.h"
#include "SqStack.c"
#include "TreeNodeSqStack.c"

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


BiTree InitExpTree(char *exp) {
    // 运算符栈
    SqStack opStack;
    InitStack(&opStack);

    // 树结点栈
    TreeNodeStack treeNodeStack;
    InitTreeNodeStack(&treeNodeStack);

    BiTNode * left;
    BiTNode * right;
    char op;

    for (int i = 0; exp[i] != '\0'; i++) {
        if (exp[i] == ' ') continue;
        if (isdigit(exp[i])) { // 如果是数字，则入操作数栈
            TreeNodeStackPush(&treeNodeStack, _CreateNode(exp[i], NULL, NULL));
        } else if (exp[i] == '(') { // 如果是左括号，则入运算符栈
            Push(&opStack, exp[i]);
        } else if (exp[i] == ')') { // 遇到了右括号
            // 只要栈顶不是左小括号
            while (GetTop(&opStack, &op) && op != '(') {
                // 那么就从树结点栈拿出两个树结点
                TreeNodeStackPop(&treeNodeStack, &right);
                TreeNodeStackPop(&treeNodeStack, &left);
                // 再从运算符栈拿出一个运算符
                Pop(&opStack, &op);

                TreeNodeStackPush(&treeNodeStack, _CreateNode(op, left, right));
            }

            // 弹出左括号
            if (GetTop(&opStack, &op) && op == '(') Pop(&opStack, NULL);
        } else {   // 遇到了运算符
            // 如果运算符栈栈顶不是左小括号，并且栈顶的运算符的优先级大于等于当前运算符
            while (GetTop(&opStack, &op) && op != '(' && precedence(op) >= precedence(exp[i])) {
                TreeNodeStackPop(&treeNodeStack, &right);
                TreeNodeStackPop(&treeNodeStack, &left);
                Pop(&opStack, &op);

                TreeNodeStackPush(&treeNodeStack, _CreateNode(op, left, right));
            }

            // 将当前运算符入运算符栈
            Push(&opStack, exp[i]);
        }
    }

    // 运算符栈中还有运算符
    while (!StackEmpty(&opStack)) {
        TreeNodeStackPop(&treeNodeStack, &right);
        TreeNodeStackPop(&treeNodeStack, &left);
        Pop(&opStack, &op);

        TreeNodeStackPush(&treeNodeStack, _CreateNode(op, left, right));
    }

    // 最后表达式树的根结点保存在树结点栈栈顶，拿出来，返回即可
    TreeNodeStackGetTop(&treeNodeStack, &left);

    DestroyTreeNodeStack(&treeNodeStack);
    DestroyStack(&opStack);
    return left;
}    