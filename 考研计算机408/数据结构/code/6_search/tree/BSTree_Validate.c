#include <stdbool.h>

#include "BSTree.h"

/* 中序遍历验证二叉排序树 */
bool IsValidBST(BSTree T) {

    BSTNode* prev = NULL;
    bool isBST = true;

    // 中序遍历以 node 为根结点的二叉树【GCC 编译器支持内嵌函数】
    void InOrder(BSTNode* node) {
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
