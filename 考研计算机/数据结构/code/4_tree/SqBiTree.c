#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

typedef struct {
    ElemType *data;
    int length;
}SqBiTree;


// 初始化顺序存储的二叉树
void InitBiTree(SqBiTree *biTree, ElemType *elems, int n) {
    biTree->data = (ElemType*)malloc(sizeof(ElemType) * n);
    for (int i = 0; i < n; i++) {
        biTree->data[i] = elems[i];
    }
    biTree->length = n;
}

// 先序遍历二叉树 T（从下标 i 开始）
void PreOrderTraverse(SqBiTree *T, int i) {
    // 如果超出了下标范围，或者是空字符则跳过
    if (i >= T->length || T->data[i] == '#')
        return;
    printf("%c-", T->data[i]);
    PreOrderTraverse(T, 2 * i + 1);
    PreOrderTraverse(T, 2 * i + 2);
}

// 中序遍历二叉树 T（从下标 i 开始）
void InOrderTraverse(SqBiTree *T, int i) {
    // 如果超出了下标范围，或者是空字符则跳过
    if (i >= T->length || T->data[i] == '#')
        return;
    InOrderTraverse(T, 2 * i + 1);
    printf("%c-", T->data[i]);
    InOrderTraverse(T, 2 * i + 2);
}

// 后序遍历二叉树 T（从下标 i 开始）
void PostOrderTraverse(SqBiTree *T, int i) {
    // 如果超出了下标范围，或者是空字符则跳过
    if (i >= T->length || T->data[i] == '#')
        return;
    PostOrderTraverse(T, 2 * i + 1);
    PostOrderTraverse(T, 2 * i + 2);
    printf("%c-", T->data[i]);
}

// 释放顺序二叉树占用的内存
void DestroyBiTree(SqBiTree *T) {
    free(T->data);
}

int main() {
    // 测试数据：按完全二叉树顺序存储，'#' 表示空结点
    char *strs = "ABC#E#G##JK";

    SqBiTree T;
    InitBiTree(&T, strs, 11);   // 11 为字符串长度

    printf("PreOrder: ");
    PreOrderTraverse(&T, 0);
    printf("\n");

    printf("InOrder: ");
    InOrderTraverse(&T, 0);
    printf("\n");

    printf("PostOrder: ");
    PostOrderTraverse(&T, 0);
    printf("\n");

    DestroyBiTree(&T);
    return 0;
}