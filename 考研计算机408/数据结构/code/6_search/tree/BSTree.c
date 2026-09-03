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
// BSTree Delete(BSTree T, KeyType key) {  // 未优化的好理解版本
//     // 先找到该key的结点，然后分其子树个数的不同情况来删除
//     BSTNode *p = T, *parent = NULL, *t, *pre;
//     while (p) {
//         if (key == p->key) 
//             break;
//         parent = p;  // 记录p的父节点，以方便删除p结点，让其孩子顶上来
//         if (key < p->key) p = p->left;
//         else if (key > p->key) p = p->right;
//     }
//     // 若找不到key的结点，直接返回根（相当于没有做修改）
//     if (!p) return T;
//     // 1.若没有左子树————可能只有右子树或者为叶子节点，则将其父节点指向该结点的右子树
//     if (!p->left) {
//         // a.若无父节点，则直接返回其孩子
//         if (!parent) {
//             T = p->right;
//             free(p);
//             return T;
//         }
//         // b.若有父节点，则将其父节点的孩子（判断左还是右）指向孩子结点的右孩子
//         if (parent->left == p)
//             parent->left = p->right;
//         else
//             parent->right = p->right;
//         free(p);
//     }
//     // 2.只有左子树
//     else if (!p->right) {
//         // 若无父节点，则直接返回其孩子
//         if (!parent) {
//             T = p->left;
//             free(p);
//             return T;
//         }
//         // 若有父节点，则将其父节点的孩子（判断左还是右）指向孩子结点的zuo孩子
//         if (parent->left == p)
//             parent->left = p->left;
//         else
//             parent->right = p->left;
//         free(p);
//     }
//     // 3.有两个孩子，则找到其前驱结点（也可以用后继，这里用前驱）
//     else {
//         // 前驱位于该结点左孩子的最右下角的位置（不仅要该前驱，还要该前驱的父节点，做他的删除操作）
//         t = p->left;
//         pre = p;
//         // 找到最右下角，并及时更新其父结点
//         while (t->right) {
//             pre = t;  // pre为前驱的父
//             t = t->right;  // t为前驱
//         }
//         // 将t的值替换p
//         p->key = t->key;
//         p->value = strdup(t->value);
//         // 更新前驱的父节点，并释放没用的前驱结点
//         // 判断 t 是 pre 的左孩子还是右孩子
//         if (t == pre->right)
//             pre->right = t->left;  // p的前驱可能还有左孩子（因为是沿着右孩子走，但无法判定是否还有没有左孩子）
//         else
//             pre->left = t->left;
//         free(t);
//     }
//     return T;
// }

// 优化版本——节省很多重复代码
// 从二叉排序树 T 中删除关键字等于 key 的结点，返回删除结点后树的根结点
BSTree Delete(BSTree T, KeyType key) {
    // 先找到该key的结点，然后分其子树个数的不同情况来删除
    BSTNode *p = T, *parent = NULL, *t, *pre;
    while (p) {
        if (key == p->key) break;
        parent = p;  // 记录p的父节点，以方便删除p结点，让其孩子顶上来
        if (key < p->key) p = p->left;
        else if (key > p->key) p = p->right;
    }
    // 若找不到key的结点，直接返回根（相当于没有做修改）
    if (!p) return T;

    t = p;  // 要删除的结点
    // 1.若没有左子树————可能只有右子树或者为叶子节点，则将其父节点指向该结点的右子树
    if (!p->left) {
        p = p->right;
        // 若无父节点，则直接返回其孩子
        if (!parent) {
            free(t);
            return p;
        }
    }
    // 2.只有左子树
    else if (!p->right) {
        p = p->left;
        // 若无父节点，则直接返回其孩子
        if (!parent) {
            free(t);
            return p;
        }
    }
    // 3.有两个孩子，则找到其前驱结点（也可以用后继，这里用前驱）
    else {
        // 前驱位于该结点左孩子的最右下角的位置（不仅要该前驱，还要该前驱的父节点，做他的删除操作）
        pre = p->left;
        parent = p;
        // 找到最右下角，并及时更新其父结点
        while (pre->right) {
            parent = pre;  // parent为前驱的父
            pre = pre->right;  // pre为前驱
        }
        // 将pre的值替换p
        p->key = pre->key;
        p->value = pre->value;

        // 删除pre结点（前驱pre无右子树）
        p = pre->left;
        // 删除的结点有一个孩子和两个孩子的情况是不同的
        t = pre;
    }

    // 将 p 的孩子上升到 p 的位置
    if (parent->left == t) parent->left = p;
    else parent->right = p;
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