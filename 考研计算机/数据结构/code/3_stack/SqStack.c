#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 顺序栈初始最大容量
#define INIT_STACK_SIZE 10

typedef int ElemType;

// 顺序栈结构体定义——采用指针的方式
typedef struct  {
    ElemType *top;
    ElemType *base;
    int maxSize;
} SqStack;

// 1. 构造一个空的顺序栈
bool InitStack(SqStack *S) {
    // 相当于动态开辟一段数组大小空间
    S->base = (ElemType*)malloc(sizeof(ElemType) * INIT_STACK_SIZE);
    S->top = S->base;
    S->maxSize = INIT_STACK_SIZE;
}

// 2. 销毁顺序栈
void DestroyStack(SqStack *S) {
    if(S)
        free(S->base);
}

// 3. 清空顺序栈
void ClearStack(SqStack *S) {
    S->top = S->base;
}

// 4. 判断栈是否为空
bool StackEmpty(SqStack *S) {
    return S->top == S->base;
}

// 5. 获取栈的长度（元素个数）
int StackLength(SqStack *S) {
    return S->top - S->base;
}

// 6. 入栈：向栈顶插入元素e
bool Push(SqStack *S, ElemType e) {
    // 插入操作肯定得先判断是否满了
    if (StackLength(S) == S->maxSize)
        return false;
    *(S->top) = e;  // 等价于*S->top = x;
    S->top++;
    return true;
}

// 7. 出栈：删除栈顶元素，用e返回其值
bool Pop(SqStack *S, ElemType *e) {
    // 删除操作肯定得先判断是否空的
    if (StackEmpty(S))
        return false;
    --S->top;
    if (e)
        *e = *(S->top);
    return true;
}

// 8. 取栈顶元素（不删除）
bool GetTop(SqStack *S, ElemType *e) {
    if (StackEmpty(S))
        return false;
    *e = *(S->top - 1);
    return true;
}

// 9. 遍历栈（从栈底到栈顶 / 栈顶到栈底均可）
void StackTraverse(SqStack *S) {
    if (StackEmpty(S))
        return;
    for (ElemType *e = S->top - 1; e > S->base; e--) {
        printf("%d-", *e);
    }
    printf("%d\n", *S->base);
}