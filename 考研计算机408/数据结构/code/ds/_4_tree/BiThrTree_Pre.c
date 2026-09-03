#include <stdio.h>
#include <stdlib.h>
#include "BiThrTree.h"

// 全局变量，用于记录前驱节点
BiThrTNode *pre;

void PreThreading(BiThrTree T) {
    if (T == NULL) return;

    // 线索化
    if (!T->left) {
        T->LTag = 1;
        T->left = pre;
    } else T->LTag = 0;     // bugfix

    if (!pre->right) {
        pre->RTag = 1;
        pre->right = T;    
    } else pre->RTag = 0;    // bugfix

    pre = T;

    if (!T->LTag) PreThreading(T->left);
    if (!T->RTag) PreThreading(T->right);
}

// 创建先序线索二叉树
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
        pre->right = head;
        pre->RTag = 1;

        // 头结点的右指针指向最后一个结点
        head->right = pre;
    }
    return head;
}

// 先序遍历先序线索二叉树
// 时间复杂度：O(n)
// 空间复杂度：O(1)
void PreOrderTraverse_Thr(BiThrTree T) {
    BiThrTree p = T->left;
    while (p != T) { // 因为先序遍历的最后一个结点是指向头结点的，所以，只要 p 不是指向头结点，就继续遍历
        printf("%c ", p->data);

        // 左子树不空，直接访问左子树
        if (p->LTag == 0) {
            p = p->left;
        } else {
            // 左子树为空，则访问右子树，如果右子树为空，则访问的是后继
            p = p->right;
        }
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