#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


//定义栈中元素的最大个数
#define INIT_MAX_SIZE 10

typedef int SElemtype;

typedef struct {
    SElemtype *base;     // 栈底指针
    SElemtype *top;      // 栈顶指针
    int maxSize;         // 栈可用的最大容量
} SqStack;

// 初始化栈
void InitStack(SqStack *S) {
    // 为顺序栈动态分配一个初始最大容量的存储空间
    S->base = (SElemtype *)malloc(sizeof(SElemtype) * INIT_MAX_SIZE);
     // 栈空时，top 和 base 的值相等，都指向栈底
    S->top = S->base;
     // 栈可用的最大容量设置为初始最大容量
    S->maxSize = INIT_MAX_SIZE;
}

// 销毁栈
void DestroyStack(SqStack *S) {
    if (S) {
        // 释放栈内存空间
        free(S->base);
    }
}

// 清空栈
// 时间复杂度：O(1)
// 空间复杂度：O(1)
void ClearStack(SqStack *S) {
    S->top = S->base;
}

// 栈判空
// 时间复杂度：O(1)
// 空间复杂度：O(1)
bool StackEmpty(SqStack *S) {
    return S->top == S->base;
}

// 查询栈长度
// 时间复杂度：O(1)
// 空间复杂度：O(1)
int StackLength(SqStack *S) {
    return S->top - S->base;
}

// 拿到栈顶元素
// 时间复杂度：O(1)
// 空间复杂度：O(1)
bool GetTop(SqStack *S, SElemtype *x) {
    // 判断如果栈空的，查询失败
    if (StackEmpty(S)) return false;
    // 拿到栈顶元素，栈顶指针减 1 指向的主存单元才是真正存储栈顶元素的位置
    *x = *(S->top - 1);
    return true;
}

// 入栈
// 时间复杂度：O(1)
// 空间复杂度：O(1)
bool Push(SqStack *S, SElemtype x) {
    // 判断栈如果满了，则直接返回
    if (StackLength(S) == S->maxSize) 
        return false;
    // 元素先入栈，栈顶指针再加 1
    *S->top = x;
    S->top++;
    return true;
}

// 出栈
// 时间复杂度：O(1)
// 空间复杂度：O(1)
bool Pop(SqStack *S, SElemtype *x) {
    // 判断如果栈空的，直接返回
    if (StackEmpty(S)) return false;
    // 栈顶指针先减 1，再将出栈的元素赋值给指针 x 指向的存储单元
    S->top--;
    if (x) *x = *S->top;
    return true;
}

// 遍历栈中所有元素
void StackTraverse(SqStack *S) {
    printf("curr SqStack, stack bottom: ");
    for (SElemtype *e = S->base; e < S->top; e++) {
        printf("%d, ", *e);
    }
    printf("\n");
}