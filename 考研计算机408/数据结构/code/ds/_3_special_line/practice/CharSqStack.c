#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// 定义栈中元素的初始最大个数
#define INIT_MAX_SIZE 50

typedef struct {
    char *base;     // 栈底指针
    char *top;      // 栈顶指针
    int maxSize;         // 栈可用的最大容量
} CharSqStack;

void InitCharStack(CharSqStack *S) {
    // 为顺序栈动态分配一个初始最大容量的数组空间
    S->base = (char *)malloc(sizeof(char) * INIT_MAX_SIZE);
    // 栈空时，top 和 base 的值相等，都指向栈底
    S->top = S->base;
    // 栈可用的最大容量设置为初始最大容量
    S->maxSize = INIT_MAX_SIZE;
}

void DestroyCharStack(CharSqStack *S) {
    // 释放栈内存空间
    free(S->base);
}

// 时间复杂度：O(1)
// 空间复杂度：O(1)
void ClearCharStack(CharSqStack *S) {
    // 将栈设置为空栈
    S->top = S->base;
}

// 时间复杂度：O(1)
// 空间复杂度：O(1)
bool CharStackEmpty(CharSqStack *S) {
    if (S->top == S->base) return true;
    else return false;
}

// 时间复杂度：O(1)
// 空间复杂度：O(1)
int CharStackLength(CharSqStack *S) {
    return S->top - S->base; 
}

// 时间复杂度：O(1)
// 空间复杂度：O(1)
bool GetTopCharStack(CharSqStack *S, char *x) {
    // 判断如果栈空的，查询失败
    if (CharStackEmpty(S)) return false;
    // 拿到栈顶元素，栈顶指针减 1 指向的主存单元才是真正存储栈顶元素的位置
    *x = *(S->top - 1);
    return true;
}

// 时间复杂度：O(1)
// 空间复杂度：O(1)
bool PushCharStack(CharSqStack *S, char x) {
    // 判断栈如果满了，则直接返回
    if (CharStackEmpty(S) == S->maxSize) 
        return false;
    // 元素先入栈，栈顶指针再加 1
    *S->top = x;
    S->top++;
    return true;
}

// 时间复杂度：O(1)
// 空间复杂度：O(1)
bool PopCharStack(CharSqStack *S, char *x) {
    // 判断如果栈空的，直接返回
    if (CharStackEmpty(S)) return false;
    // 栈顶指针先减 1，再将出栈的元素赋值给指针 x 指向的存储单元
    S->top--;
    if (x != NULL) *x = *S->top;
    return true;
}

// 时间复杂度：O(n)，n 表示栈内元素的个数
// 空间复杂度：O(1)
void CharStackTraverse(CharSqStack *S) {
    printf("curr SqStack, stack bottom: ");
    // 从栈底元素开始，遍历打印每个元素，到栈顶元素结束
    for (char *e = S->base; e < S->top; e++) {
        printf("%d, ", *e);
    }
    printf("\n");
}