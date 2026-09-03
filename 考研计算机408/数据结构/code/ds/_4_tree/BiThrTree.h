#ifndef BITHRTREE_H

#define BITHRTREE_H

#include <stdio.h>
#include <stdlib.h>

typedef char TElemType;

typedef struct BiThrTNode {
    TElemType data;          // 数据域

    struct BiThrTNode *left;    // 左指针域
    struct BiThrTNode *right;   // 右指针域

    // 左标志
    int LTag;  // 等于 0 表示 left 指向左孩子，等于 1 表示 left 指向前驱  
    // 右标志
    int RTag;  // 等于 0 表示 right 指向右孩子，等于 1 表示 right 指向后继
} BiThrTNode, *BiThrTree;

BiThrTNode * CreateNode(TElemType data) {
    BiThrTNode *newNode = (BiThrTNode *)malloc(sizeof(BiThrTNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    // 还没有进行线索化，此时即使是指向空，也并不代表指向前驱后继
    newNode->LTag = 0;
    newNode->RTag = 0;
    return newNode;
}

BiThrTree CreateBiTree(char* strs, int n, int i) {
    if (i >= n || strs[i] == '#') return NULL;

    BiThrTree T = CreateNode(strs[i]);

    T->left = CreateBiTree(strs, n, 2 * i + 1);
    T->right = CreateBiTree(strs, n, 2 * i + 2);

    return T;
}  

#endif