#include <stdio.h>
#include <stdlib.h>
#include "BiThrTree.h"

BiThrTNode *pre;

// 先序线索化
void PreThreading(BiThrTree T) {
    if (!T) return;

    // 进行线索化——根-左-右
    // 先判断左子树的左tag
    if (T->left)
        T->lTag = 0;
    // 若没有左子树，则需要指定其前驱了
    else {
        T->lTag = 1;
        T->left = pre;
    }

    // 再判断pre的右tag
    if (pre->right) 
        pre->rTag = 0;
    else {
        pre->rTag = 1;
        pre->right = T;
    }

    pre = T;
    // 递归线索化左右孩子——递归前先判断左右标记是否是线索
    if (!T->lTag)
        PreThreading(T->left);
    if (!T->rTag)
        PreThreading(T->right);
}

// 递归创建先序线索二叉树————主要是针对头节点的创建和初始化的过程
BiThrTree PreOrderThreading(BiThrTree T) {
    BiThrTree head = (BiThrTree)malloc(sizeof(BiThrTNode));
    head->lTag = 0;
    // 右指针初始时为1，且指向自己
    head->rTag = 1;
    head->right = head;

    // 若无根节点（空）
    if (!T) 
        head->left = head;
    else {
        head->left = T;

        // 初始化pre
        pre = head;

        // 线索化当前已经创建好的二叉树
        PreThreading(T);  // 运行完后，pre指向最后一个结点

        // 再将最后一个结点和头节点连上
        pre->right = head;
        pre->rTag = 1;
        head->right = pre;
    }

    return head;
}

// 先序遍历先序线索二叉树
// 时间复杂度：O(n)
// 空间复杂度：O(1)
void PreOrderTraverse_Thr(BiThrTree T) {
    BiThrTree p = T->left;
    // 若头节点的左指针指向头节点T则表示，树空，否则就while循环
    while (p != T) {
        // 根左右
        printf("%c-", p->data);

        // 也就是有左指针就先访问，因为遵循的是根-左-右，先左后右
        if (!p->lTag)
            p = p->left;
        // 左指针如果没有，还可以通过线索访问到它的后继
        else
            p = p->right;
    }
}

int main() {
    char *strs = "ABD#ECF########";
    int n = 15;

    BiThrTree root = CreateBiTree(strs, n, 0);
    BiThrTree head = PreOrderThreading(root);

    printf("先序遍历结果: ");
    PreOrderTraverse_Thr(head);

    return 0;
}