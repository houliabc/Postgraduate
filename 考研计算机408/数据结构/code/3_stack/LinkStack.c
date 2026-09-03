#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef int Elemtype;

typedef struct StackNode {
    Elemtype data;
    struct StackNode *next;
}StackNode, *LinkStack; // 一级指针，指向栈中的结点

// 初始化栈——因为是链表，故不需要指定大小空间
void InitStack(LinkStack *S) {  // 因为要修改S，所以传入了一个指针的指针，也就是栈中结点的指针
    // S是头指针的意思，传入的是二级指针，需要解引用成一级指针，才表示栈中结点的指针
    *S = NULL;
}

// 销毁栈
void DestroyStack(LinkStack S) {
    StackNode *tmp, *cur = S;
    while (cur) {
        tmp = cur;
        cur = cur->next;
        free(tmp);
    }
}

// 清空栈
void ClearStack(LinkStack *S) {
    DestroyStack(*S);
    *S = NULL;
}

// 栈判空
bool StackEmpty(LinkStack S) {
    return S == NULL;
}

// 查询栈长度
int StackLength(LinkStack S) {
    StackNode *cur = S;
    int i = 0;
    while (cur) {
        i++;
        cur = cur->next;
    }
    return i;
}

// 拿到栈顶元素
bool GetTop(LinkStack S, Elemtype *x) {
    if (StackEmpty(S))
        return false;
    *x = S->data;
    return true;
}

// 入栈
bool Push(LinkStack *S, Elemtype x) {
    // 只有需要加入新节点或者头节点时，才需要malloc
    StackNode *in = (StackNode*)malloc(sizeof(StackNode));
    in->data = x;
    in->next = *S;
    *S = in;
    return true;
}

// 出栈
bool Pop(LinkStack *S, Elemtype *x) {
    if (StackEmpty(*S))
        return false;
    StackNode *cur = *S;  // S的值本身就表示的是指针，而传入进来*S就是指针的指针，故需要解引用
    *x = cur->data;
    *S = cur->next;
    free(cur);
    return true;
}

// 遍历栈中所有元素
void StackTraverse(LinkStack S) {
    if (StackEmpty(S))
        return;
    StackNode *cur = S;
    // 第一步：先输出第一个元素
    printf("%d", cur->data);
    cur = cur->next;

    // 第二步：后续元素 先输出-，再输出值
    while (cur) {
        printf("-%d", cur->data);
        cur = cur->next;
    }
    // 最后换行
    printf("\n");
}