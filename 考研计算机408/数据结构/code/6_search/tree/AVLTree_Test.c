#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "AVLTree.c"

/* 中序遍历验证二叉排序树 */
bool IsValidBST(AVLTree T) {
    AVLTNode* prev = NULL;
    bool isBST = true;

    // 中序遍历以 node 为根结点的二叉树【GCC 编译器支持内嵌函数】
    void InOrder(AVLTNode* node) {
        if (!node) return;

        InOrder(node->left);
        // 处理当前结点
        // 如果有前一个结点，且前一个结点的关键字大于等于当前结点关键字，那么就不符合 BST 性质了
        if (prev && prev->key >= node->key) {
            isBST = false;
            return;
        }
        // 将当前结点设置为前一个结点
        prev = node;
        InOrder(node->right);
    }
    
    InOrder(T);
    return isBST;
}

// 判断一棵二叉排序树是否是平衡二叉树
bool IsBalanced(AVLTree T) {
    if (!T) return true;

    int bf = GetBalanceFactor(T);
    // 如果当前顶点的平衡因子绝对值大于 1，那么就不是平衡二叉树
    if (abs(bf) > 1) return false;

    // 否则，左右子树都是平衡的，那么整棵树就是平衡的
    return IsBalanced(T->left) && IsBalanced(T->right);
}


int main() {
    AVLTree T = NULL;

    T = Put(T, 2, "net");
    T = Put(T, 10, "os");
    T = Put(T, 8, "laotang");
    //T = Put(T, 12, "douma");
    //T = Put(T, 13, "algo");
    //T = Put(T, 16, "lisi");
    //T = Put(T, 20, "ds");
    //T = Put(T, 25, "computer");
    

    printf("is bst : %d\n", IsValidBST(T));
    printf("is balance tree : %d\n", IsBalanced(T));


    DestroyAVLTree(T);

    return 0;
}