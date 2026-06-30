// BSTree.c
#include <stdio.h>
#include <string.h>
#include "BSTree.h"

// 获取键 key 对应的值（若 key 不存在，则返回 NULL）
// 时间复杂度：O(h)
ValueType Get(BSTree T, KeyType key) {
    if (!T) return NULL;
    if (T->key == key)
        return T->value;
    else if (key < T->key) return Get(T->left, key);
    else return Get(T->right, key);
    return NULL;
}

// 将键值对存入表中，并返回 BST 的根结点————如果key已存在，则修改现有key对应的value
// 时间复杂度：O(h)
// 递归实现
BSTree Put(BSTree T, KeyType key, ValueType value) {
    BSTNode *newNode = CreateNode(key, value);
    //如果是空树，直接返回新建结点
    if (!T) return newNode;

    // 否则插入到某个结点下面作为叶子结点
    if (key == T->key) {
        T->value = strdup(value);  // 相同，则不插入，而修改对应的value值
        return T;
    }
    // 左边
    else if (key < T->key) T->left = Put(T->left, key, value);
    // 右边
    else T->right = Put(T->right, key, value);

    return T;
}

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