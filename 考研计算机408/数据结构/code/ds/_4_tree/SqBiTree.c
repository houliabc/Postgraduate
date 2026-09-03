#include <stdio.h>
#include <stdlib.h>

typedef char TElemType;

typedef struct {
    TElemType *nodes;  // 顺序存储二叉树的数组
    int elemNum;       // 二叉树结点数量
} SqBiTree;

// 初始化顺序存储的二叉树
void InitBiTree(SqBiTree *biTree, TElemType *elems, int n) {
    biTree->nodes = (TElemType *) malloc(sizeof(TElemType) * n);
    for (int i = 0; i < n; i++) {
        biTree->nodes[i] = elems[i];
    }
    biTree->elemNum = n;
}

// 先序遍历二叉树 T
void PreOrderTraverse(SqBiTree *T, int i) {
    if (i >= T->elemNum || T->nodes[i] == '#') return;

    // 打印根节点的值，表示访问根结点
    printf("%c, ", T->nodes[i]);

    // 先序遍历左子树
    PreOrderTraverse(T, 2 * i + 1);

    // 先序遍历右子树
    PreOrderTraverse(T, 2 * i + 2);
}

int main() {

    char * strs = "ABC#E#G##JK";

    SqBiTree T;
    InitBiTree(&T, strs, 11);

    PreOrderTraverse(&T, 0);

    return 0;
}