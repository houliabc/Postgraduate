#ifndef BSTREE_H

#define BSTREE_H

#include <stdlib.h>

typedef int KeyType;
typedef char* ValueType;

// 二叉树排序树结点
typedef struct node {
    KeyType key;        // 关键字
    ValueType value;    // 值
    struct node *left;  // 左孩子指针
    struct node *right; // 右孩子指针
} BSTNode, *BSTree;

// 创建新结点
BSTNode *CreateNode(KeyType key, ValueType value) {
    BSTNode *newNode = (BSTNode *) malloc (sizeof(BSTNode));
    newNode->key = key;
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void DestroyBSTree(BSTree T) {
    if (!T) return;

    DestroyBSTree(T->left);
    DestroyBSTree(T->right);
    free(T);
}

#endif