#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

//定义栈中元素的最大个数
#define INIT_MAX_SIZE 10

typedef int SElemtype;

typedef struct {
    SElemtype *data;     // 数组基地址
    int top;             // 指向栈顶的数组下标
    int maxSize;         // 栈可用的最大容量
} SqStack;

// 初始化栈
void InitStack(SqStack *S) {
    // 为顺序栈动态分配一个初始最大容量的存储空间
    S->data = (SElemtype *)malloc(sizeof(SElemtype) * INIT_MAX_SIZE);
    // 初始为空栈
    S->top = -1;
     // 栈可用的最大容量设置为初始最大容量
    S->maxSize = INIT_MAX_SIZE;
}

// 销毁栈
void DestroyStack(SqStack *S) {
    if (S) {
        // 释放栈内存空间
        free(S->data);
    }
}

// 清空栈
// 时间复杂度：O(1)
// 空间复杂度：O(1)
void ClearStack(SqStack *S) {
    S->top = -1;
}

// 栈判空
// 时间复杂度：O(1)
// 空间复杂度：O(1)
bool StackEmpty(SqStack *S) {
    return S->top == -1;
}

// 查询栈长度
// 时间复杂度：O(1)
// 空间复杂度：O(1)
int StackLength(SqStack *S) {
    return S->top + 1;
}

// 拿到栈顶元素
// 时间复杂度：O(1)
// 空间复杂度：O(1)
bool GetTop(SqStack *S, SElemtype *x) {
    // 判断如果栈空的，查询失败
    if (StackEmpty(S)) return false;
    // 拿到栈顶元素，栈顶指针指向的主存单元是真正存储栈顶元素的位置
    *x = S->data[S->top];
    return true;
}

// 入栈
// 时间复杂度：O(1)
// 空间复杂度：O(1)
bool Push(SqStack *S, SElemtype x) {
    // 判断栈如果满了，则直接返回
    if (StackLength(S) == S->maxSize) 
        return false;
    // 栈顶下标先加 1，再入栈
    S->top++;
    S->data[S->top] = x;
    
    return true;
}

// 出栈
// 时间复杂度：O(1)
// 空间复杂度：O(1)
bool Pop(SqStack *S, SElemtype *x) {
    if (!GetTop(S, x)) return false;

    S->top--;
    
    return true;
}

// 遍历栈中所有元素
void StackTraverse(SqStack *S) {
    printf("curr SqStack, stack bottom: ");
    for (int i = 0; i <= S->top; i++) {
        printf("%d, ", S->data[i]);
    }
    printf("\n");
}