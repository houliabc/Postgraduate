#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef int SElemtype;

typedef struct StackNode {
    SElemtype data;          // 数据域
    struct StackNode *next; // 指针域
} StackNode, *LinkStack;

// 初始化栈
void InitStack(LinkStack *S) {
    *S = NULL;
}

// 销毁栈
void DestroyStack(LinkStack S) {
    // 遍历每个结点时，释放掉结点占用内存
    StackNode *tmp;
    StackNode *p = S;
    while (p) {
        tmp = p;
        p = p->next;
        free(tmp);
    }
}

// 清空栈
void ClearStack(LinkStack *S) {
    // 释放所有结点占的内存空间
    DestroyStack(*S);
    // 将头指针指向空
    *S = NULL;
}

// 栈判空
// 时间复杂度：O(1)
// 空间复杂度：O(1)
bool StackEmpty(LinkStack S) {
    return S == NULL;
}

// 查询栈长度
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int StackLength(LinkStack S) {
    int n = 0;
    StackNode *p = S; 
    while (p) {
        n++;
        p = p->next;
    }
    return n;
}

// 拿到栈顶元素
// 时间复杂度：O(1)
// 空间复杂度：O(1)
bool GetTop(LinkStack S, SElemtype *x) {
    if (StackEmpty(S)) return false;
    *x = S->data;
    return true;
}

// 入栈
// 时间复杂度：O(1)
// 空间复杂度：O(1)
bool Push(LinkStack *S, SElemtype x) {
    StackNode *p = (StackNode *)malloc(sizeof(StackNode));
    p->data = x;

    p->next = *S;
    *S = p;
    return true;
}

// 出栈
// 时间复杂度：O(1)
// 空间复杂度：O(1)
bool Pop(LinkStack *S, SElemtype *x) {
    if (StackEmpty(*S)) return false;
    if (x) *x = (*S)->data;

    StackNode *p = *S;
    *S = (*S)->next;

    free(p);
    return true;
}

// 遍历栈中所有元素
void StackTraverse(LinkStack S) {
   printf("curr LinkStack, stack top: ");
    StackNode *p = S;
    while (p) {
        printf("%d, ", p->data);
        p = p->next;
    }
    printf("\n");
}