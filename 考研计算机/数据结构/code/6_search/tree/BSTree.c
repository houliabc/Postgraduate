// BSTree.c
#include <stdio.h>
#include <string.h>
#include "BSTree.h"

// 获取键 key 对应的值（若 key 不存在，则返回 NULL）
// 时间复杂度：O(h)
ValueType Get(BSTree T, KeyType key) {
    BSTNode *p = T;
    while (p) {
        if (key < p->key)
            p = p->left;
        else if (key > p->key)
            p = p->right;
        else
            return p->value;
    }
    return NULL;
}

// 将键值对存入表中，并返回 BST 的根结点————如果key已存在，则修改现有key对应的value
// 时间复杂度：O(h)
BSTree Put(BSTree T, KeyType key, ValueType value) {
    BSTNode *p = T, *parent = NULL;
    while (p) {
        parent = p;
        if (key < p->key)
            p = p->left;
        else if (key > p->key)
            p = p->right;
        // 如果key已存在，则修改现有key对应的value
        else {
            p->value = strdup(value);
            return T;
        }
    }
    // key不存在就新建一个叶子节点
    BSTNode *newNode = CreateNode(key, value);

    //如果是空树，直接返回新建结点
    if (!parent) return newNode;

    // 否则插入到parent下面————作为叶子节点
    if (key < parent->key)
        parent->left = newNode;
    else
        parent->right = newNode;

    return T;
}

// 从二叉排序树 T 中删除关键字等于 key 的结点，返回删除结点后树的根结点
BSTree Delete(BSTree T, KeyType key) {
    // 先找到该key的结点，然后分其子树个数的不同情况来删除
    BSTNode *p = T, *parent = NULL, *t, *pre;
    while (p) {
        if (key == p->key) 
            break;
        parent = p;
        if (key < p->key) p = p->left;
        else if (key > p->key) p = p->right;
    }

    // 若找不到key的结点，直接返回根（相当于没有做修改）
    if (!p) return T;

    t = p;
    // 若没有左子树————可能只有右子树或者为叶子节点
    if (!p->left) {
        p = p->right;
        // 若删的是根节点
        if (!parent) {
            free(t);  // 释放根结点
            return p;
        }
    }
    // 只有左子树
    else if (!p->right) {
        p = p->left;
        // 若删的是根节点
        if (!parent) {
            free(t);  // 释放根结点
            return p;
        }
    }
    // 有两个孩子，则找到其前驱结点
    else {
        pre = p->left;  // 被删结点的前驱一定是在其左子树的最右下角的位置的
        parent = p;  // 时刻记录前驱结点的父节点
        // 有右子树就一直往右下角走
        while (pre->right) {
            parent = pre;
            pre = pre->right;
        }

        // 更新各自指针：将前驱的数据覆盖被删数据
        p->key = pre->key;
        p->value = pre->value;

        // 删除pre结点（前驱pre无右孩子）
        p = pre->left;

        t = pre;
    }

    // 将p的孩子上升到p的位置
    if (t == parent->left) {
        parent->left = p;
    }
    else
        parent->right = p;
    free(t);
    return T;
}

int main() {
    BSTree T = NULL;

    T = Put(T, 10, "laotang");
    T = Put(T, 12, "douma");
    T = Put(T, 13, "algo");
    T = Put(T, 8, "os");
    T = Put(T, 2, "net");

    printf("key = 8, value = %s\n", Get(T, 8)); // os
    printf("key = 12, value = %s\n", Get(T, 12)); // douma

    T = Put(T, 12, "data structure");
    printf("key = 12, value = %s\n", Get(T, 12)); // data structure

    T = Delete(T, 8);
    printf("key = 8, value = %s\n", Get(T, 8)); // null

    DestroyBSTree(T);

    return 0;
}