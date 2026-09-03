#include <stdio.h>
#include <stdlib.h>

#include "BiThrTree.h"

// 全局变量，用于记录前驱节点
BiThrTNode *pre;

void PostThreading(BiThrTree T) {
    if (T == NULL) return;

    if (!T->LTag) PostThreading(T->left);
    if (!T->RTag) PostThreading(T->right);

    // 线索化
    if (!T->left) {
        T->LTag = 1;
        T->left = pre;
    } else T->LTag = 0;         // bugfix

    if (!pre->right) {
        pre->RTag = 1;
        pre->right = T;
    } else pre->RTag = 0;       // bugfix

    pre = T;
}

// 创建后序线索二叉树
BiThrTree PreOrderThreading(BiThrTree T) {
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
        if (!pre->right) {
            pre->right = head;
            pre->RTag = 1;
        }
    }
    return head;
}

// 后序遍历后序线索二叉树
// 时间复杂度：O(n)
// 空间复杂度：O(1)
void PostOrderTraverse_Thr(BiThrTree T) {
    // TODO
}
