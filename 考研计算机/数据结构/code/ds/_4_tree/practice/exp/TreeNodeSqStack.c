#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "../../BiTree.h"

#define INIT_MAX_SIZE 50

typedef BiTNode * TSElemtype;

typedef struct {
    TSElemtype *data;     // 数组基地址（存放二叉树结点指针）
    int top;            // 指向栈顶的数组下标
    int maxSize;         // 栈可用的最大容量
} TreeNodeStack;

void InitTreeNodeStack(TreeNodeStack *S) {
    // 为顺序栈动态分配一个初始最大容量的数组空间
    S->data = (TSElemtype *)malloc(sizeof(TSElemtype) * 50);
    // 初始为空栈
    S->top = -1;
    // 栈可用的最大容量设置为初始最大容量
    S->maxSize = INIT_MAX_SIZE;
}

void DestroyTreeNodeStack(TreeNodeStack *S) {
    // 释放栈内存空间
    free(S->data);
}

bool TreeNodeStackEmpty(TreeNodeStack *S) {
    if (S->top == -1) return true;
    else return false;
}


bool TreeNodeStackGetTop(TreeNodeStack *S, TSElemtype *x) {
    // 判断如果栈空的，直接返回
    if (TreeNodeStackEmpty(S)) return false;
    *x = S->data[S->top];
    return true;
}

bool TreeNodeStackPush(TreeNodeStack *S, TSElemtype x) {
    // 判断栈如果满了，则直接返回
    if (S->top == S->maxSize - 1) 
        return false;
    // 栈顶下标先加 1，再入栈
    S->data[++S->top] = x;
    return true;
}

bool TreeNodeStackPop(TreeNodeStack *S, TSElemtype *x) {
    // 判断如果栈空的，直接返回
    if (S->top == -1) return false;
    
    if (x != NULL) {
        // 先出栈，指针再减 1
        *x = S->data[S->top];
    } 
    S->top--;
    return true;
}