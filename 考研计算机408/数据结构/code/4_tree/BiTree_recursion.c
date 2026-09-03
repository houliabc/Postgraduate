#include <stdio.h>
#include "BiTree.h"

// ---- 递归实现二叉树的先、中、后序遍历 --------

// 先序遍历二叉树 T
void PreOrderTraverse(BiTree T) {
    if (!T)
        return;
    printf("%c-", T->data);
    PreOrderTraverse(T->left);
    PreOrderTraverse(T->right);
}

// 中序遍历二叉树 T
void InOrderTraverse(BiTree T) {
    if (!T)
        return;
    InOrderTraverse(T->left);
    printf("%c-", T->data);
    InOrderTraverse(T->right);
}

// 后序遍历二叉树 T
void PostOrderTraverse(BiTree T) {
    if (!T)
        return;
    PostOrderTraverse(T->left);
    PostOrderTraverse(T->right);
    printf("%c-", T->data);
}

int main() {
    BiTree T = GetTestBiTree();
    
    printf("PreOrderTraverse Seq: ");
    PreOrderTraverse(T);
    printf("\n");

    printf("InOrderTraverse Seq: ");
    InOrderTraverse(T);
    printf("\n");

    printf("PostOrderTraverse Seq: ");
    PostOrderTraverse(T);
    printf("\n");
    
    return 0;
}