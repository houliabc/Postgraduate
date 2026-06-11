#ifndef BITREE_H
#define BITREE_H
#include <stdlib.h>

typedef char cElemType;
typedef struct BiTNode {
    cElemType data;
    struct BiTNode *left;
    struct BiTNode *right;
} BiTNode, *BiTree;

// 创建一个包含数据域、左右指针域的二叉树结点
BiTNode * _CreateNode(char data, BiTNode *left, BiTNode *right) {
    BiTNode *newNode = (BiTNode*)malloc(sizeof(BiTNode));
    newNode->data = data;
    newNode->left = left;
    newNode->right = right;
    return newNode;
}

// 创建一个只包含数据域的二叉树结点
BiTNode * CreateNode(char data) {
    BiTNode *newNode = (BiTNode*)malloc(sizeof(BiTNode));
    newNode->data = data;
    return newNode;
}

// // 构建以 strs[i] 为根结点的树，并返回树的根节点
BiTNode* CreateTree(char* strs, int n, int i) {
    if (i >= n || strs[i] == '#') return NULL;
    BiTNode *T = CreateNode(strs[i]);
    // 构建以 strs[2*i + 1] 为根结点的左子树，并返回左子树的根节点
    T->left = CreateTree(strs, n, 2 * i + 1);
    // 构建以 strs[2*i + 2] 为根结点的右子树，并返回右子树的根节点
    T->right = CreateTree(strs, n, 2 * i + 2);
    return T;
}

// // 拿到一棵测试的二叉树
BiTNode* GetTestBiTree() {
    char * strs = "ABCDEFH#I######";
    BiTree T = CreateTree(strs, 15, 0);
    return T;
}

// // 释放树的内存
// void freeTree(BiTNode* root) {
// }

#endif