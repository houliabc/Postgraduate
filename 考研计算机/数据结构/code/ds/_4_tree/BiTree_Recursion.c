#include <stdio.h>

#include "BiTree.h"

// ---- 递归实现二叉树的先、中、后序遍历 --------

// 先序遍历二叉树 T
void PreOrderTraverse(BiTree T) {
    if (T == NULL) return;

    // 打印根节点的值，表示访问根结点
    printf("%c, ", T->data);

    // 先序遍历左子树
    PreOrderTraverse(T->left);

    // 先序遍历右子树
    PreOrderTraverse(T->right);
}

 
// 中序遍历二叉树 T
void InOrderTraverse(BiTree T) {
    if (T == NULL) return;
    
    // 中序遍历左子树
    InOrderTraverse(T->left);

    // 打印根节点的值，表示访问根结点
    printf("%c, ", T->data);

    // 中序遍历右子树
    InOrderTraverse(T->right);
}
   
// 后序遍历二叉树 T
void PostOrderTraverse(BiTree T) {
    if (T == NULL) return;

    // 后序遍历左子树
    PostOrderTraverse(T->left);

    // 后序遍历右子树
    PostOrderTraverse(T->right);
    
    // 打印根节点的值，表示访问根结点
    printf("%c, ", T->data);
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
}