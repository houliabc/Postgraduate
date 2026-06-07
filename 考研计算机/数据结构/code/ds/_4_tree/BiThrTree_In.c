#include <stdio.h>
#include <stdlib.h>

#include "BiThrTree.h"

// 全局变量，用于记录前驱节点
BiThrTNode *pre;

void InThreading(BiThrTree T) {
    if (T == NULL) return;

    if (!T->LTag) InThreading(T->left);

    // 线索化
    if (!T->left) {
        T->LTag = 1;
        T->left = pre;
    } else T->LTag = 0;     // bugfix

    if (!pre->right) {
        pre->RTag = 1;
        pre->right = T;
    } else pre->RTag = 0;

    pre = T;

    if (!T->RTag) InThreading(T->right);
}

// 创建中序线索二叉树
BiThrTree InOrderThreading(BiThrTree T) {
    // 创建一个头结点
    BiThrTree head;
    head = (BiThrTree)malloc(sizeof(BiThrTNode));

    // 头结点的左标志为 0，如果树非空的话，则左指针指向树根结点
    head->LTag = 0;

    // 头结点的右标志为 1，右指针初始化指向自己
    head->RTag = 1;
    head->right = head;

    if (!T) {
        head->left = head;
    } else {
        head->left = T;

        // pre 初始化指向头结点
        pre = head;

        // 然后将二叉树 T 进行先序线索化
        PreThreading(T);

        // 将最后一个结点的右指针指向头节点
        pre->right = head;
        pre->RTag = 1;

        // 头结点的右指针指向最后一个结点
        head->right = pre;
    }
    return head;
}

// 中序遍历中序线索二叉树
// 时间复杂度：O(n)
// 空间复杂度：O(1)
void InOrderTraverse_Thr(BiThrTree T) {
    BiThrTree p = T->left;
    while (p != T) {
        // 一直沿着左子树走，直到 p 的左子树为空
        while (p -> LTag == 0) p = p->left;

        // 访问打印结点 p
        printf("%c ", p->data);

        // 如果结点 p 有后继，则一直访问后继
        while (p->RTag == 1 && p->right != T) {
            p = p->right;
            printf("%c ", p->data);
        }

        p = p->right;
    }
}
