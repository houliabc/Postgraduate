#ifndef BITREE_H
#define BITREE_H
#include <stdlib.h>

typedef char cElemType;
typedef struct BiThrTNode {
    cElemType data;
    struct BiThrTNode *left;
    struct BiThrTNode *right;
    // 1表示指向前驱后继，否则表示指向左右孩子
    int lTag, rTag;
} BiThrTNode, *BiThrTree;

// 创建一个包含数据域、左右指针域的二叉树结点
BiThrTNode * _CreateNode(char data, BiThrTNode *left, BiThrTNode *right) {
    BiThrTNode *newNode = (BiThrTNode*)malloc(sizeof(BiThrTNode));
    newNode->data = data;
    newNode->left = left;
    newNode->right = right;
    newNode->lTag = 0;
    newNode->rTag = 0;
    return newNode;
}

// 创建一个只包含数据域的二叉树结点
BiThrTNode * CreateNode(char data) {
    BiThrTNode *newNode = (BiThrTNode*)malloc(sizeof(BiThrTNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->lTag = 0;
    newNode->rTag = 0;
    return newNode;
}

// 构建以 strs[i] 为根结点的树，并返回树的根节点————也就是将一个顺序二叉树，转化为链式二叉树
BiThrTree CreateBiTree(char* strs, int n, int i) {
    if (i >= n || strs[i] == '#') return NULL;
    // 创建根节点
    BiThrTNode *T = CreateNode(strs[i]);
    // 构建以 strs[2*i + 1] 为根结点的左子树，并返回左子树的根节点
    T->left = CreateBiTree(strs, n, 2 * i + 1);
    // 构建以 strs[2*i + 2] 为根结点的右子树，并返回右子树的根节点
    T->right = CreateBiTree(strs, n, 2 * i + 2);
    return T;
}

// 拿到一棵测试的二叉树
BiThrTNode* GetTestBiTree() {
    char * strs = "ABCDEFH#I######";
    BiThrTree T = CreateBiTree(strs, 15, 0);
    return T;
}

// 释放树的内存————也是在遍历的基础上去做一个释放内存的操作的
void freeTree(BiThrTNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

#endif