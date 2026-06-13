#include <stdio.h>
#include <stdlib.h>
#include "BiThrTree.h"

BiThrTNode *pre;

// 中序线索化
void InThreading(BiThrTree T) {
    if (!T) return;

    // 递归线索化左右孩子——递归前先判断左右标记是否是线索
    if (!T->lTag)
        InThreading(T->left);

    // 对根节点的处理
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

    // 右结点
    if (!T->rTag)
        InThreading(T->right);
}

// 递归创建中序线索二叉树————主要是针对头节点的创建和初始化的过程
BiThrTree InOrderThreading(BiThrTree T) {
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
        InThreading(T);  // 运行完后，pre指向最后一个结点

        // 再将最后一个结点和头节点连上
        pre->right = head;
        pre->rTag = 1;
        head->right = pre;
    }

    return head;
}

// 中序遍历中序线索二叉树
// 时间复杂度：O(n)
// 空间复杂度：O(1)
void InOrderTraverse_Thr(BiThrTree T) {
    BiThrTree p = T->left;
    // 若头节点的左指针指向头节点T则表示，树空，否则就while循环
    while (p != T) {
        // 若有左孩子，就一直走到底
        while (!p->lTag)
            p = p->left;

        // 根
        printf("%c-", p->data);

        // 如果该结点有后继，则一直访问下去（沿着一路去输出）
        while (p->rTag && p->right != T) {
            p = p->right;
            printf("%c-", p->data);
        }
           
        // 右
        p = p->right;
    }
}

int main() {
    char *strs = "ABD#ECF########";
    int n = 15;

    BiThrTree root = CreateBiTree(strs, n, 0);
    BiThrTree head = InOrderThreading(root);

    printf("中序遍历结果: ");
    InOrderTraverse_Thr(head);

    return 0;
}