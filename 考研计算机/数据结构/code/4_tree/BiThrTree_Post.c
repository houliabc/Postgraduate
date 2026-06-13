#include <stdio.h>
#include <stdlib.h>
#include "BiThrTree.h"

BiThrTNode *pre;

// 后序线索化
void PostThreading(BiThrTree T) {
    if (!T) return;

    // 递归线索化左右孩子——递归前先判断左右标记是否是线索
    if (!T->lTag)
        PostThreading(T->left);
    // 右结点
    if (!T->rTag)
        PostThreading(T->right);

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

}

// 递归创建后序线索二叉树————主要是针对头节点的创建和初始化的过程
BiThrTree PostOrderThreading(BiThrTree T) {
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
        PostThreading(T);  // 运行完后，pre指向最后一个结点

        // 将最后一个结点的右指针指向头结点
        if (!pre->right) {
            pre->right = head;
            pre->rTag = 1;
        }
    }

    return head;
}

// 后序遍历后序线索二叉树
// 时间复杂度：O(n)
// 空间复杂度：O(1)
void PostOrderTraverse_Thr(BiThrTree T) {
    // 过于困难，略
}

int main() {
    char *strs = "ABD#ECF########";
    int n = 15;

    BiThrTree root = CreateBiTree(strs, n, 0);
    BiThrTree head = PostOrderThreading(root);

    printf("后序遍历结果: ");
    PostOrderTraverse_Thr(head);

    return 0;
}