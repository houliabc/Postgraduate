#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 顺序栈初始最大容量
#define INIT_STACK_SIZE 10

typedef int ElemType;

// 顺序栈结构体定义——采用指针的方式
typedef struct  {
    ElemType *data;
    int top;
    int maxSize;
} SqStack;

// 1. 构造一个空的顺序栈
void InitStack(SqStack *S) {
    // 相当于动态开辟一段数组大小空间
    S->data = (ElemType*)malloc(sizeof(ElemType) * INIT_STACK_SIZE);
    S->top = -1;
    S->maxSize = INIT_STACK_SIZE;
}

// 2. 销毁顺序栈
void DestroyStack(SqStack *S) {
    if(S)
        free(S->data);
}

// 3. 清空顺序栈
void ClearStack(SqStack *S) {
    S->top = -1;
}

// 4. 判断栈是否为空
bool StackEmpty(SqStack *S) {
    return S->top == -1;
}

// 5. 获取栈的长度（元素个数）
int StackLength(SqStack *S) {
    return S->top + 1;
}

// 6. 入栈：向栈顶插入元素e
bool Push(SqStack *S, ElemType e) {
    // 插入操作肯定得先判断是否满了
    if (StackLength(S) == S->maxSize)
        return false;
    S->data[++S->top] = e;  
    return true;
}

// 7. 出栈：删除栈顶元素，用e返回其值
bool Pop(SqStack *S, ElemType *e) {
    // 删除操作肯定得先判断是否空的
    if (StackEmpty(S))
        return false;
    if (e)
        *e = S->data[S->top--];
    return true;
}

// 8. 取栈顶元素（不删除）
bool GetTop(SqStack *S, ElemType *e) {
    if (StackEmpty(S))
        return false;
    *e = S->data[S->top];
    return true;
}

// 9. 遍历栈（从栈底到栈顶 / 栈顶到栈底均可）
void StackTraverse(SqStack *S) {
    if (StackEmpty(S))
        return;
    for (int i = S->top; i > 0; i--) {
        printf("%d-", S->data[i]);
    }
    printf("%d\n", S->data[0]);
}