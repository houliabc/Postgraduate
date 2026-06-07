#include <stdio.h>
#include <string.h>

#include "BSTree.h"

// 在二叉查找树 T 中，查找并返回关键字 key 对应的 value
// 时间复杂度：O(logn)
// 空间复杂度：O(logn)
ValueType Get(BSTree T, KeyType key) {
    if (!T) return NULL;
    if (key == T->key) return T->value;
    else if (key < T->key) return Get(T->left, key);
    else return Get(T->right, key);
}

// 在二叉排序树 T 中，插入指定键值对，并返回插入了结点后的 BST 的根结点
// 时间复杂度：O(logn)
// 空间复杂度：O(logn)
BSTree Put(BSTree T, KeyType key, ValueType value) {
    // 如果树是空的，则创建一个新的结点并返回
    if (!T) return CreateNode(key, value);
    if (key == T->key) {
        T->value = strdup(value);
        return T;
    }

    if (key < T->key) {
        T->left = Put(T->left, key, value);
    } else {
        T->right = Put(T->right, key, value);
    }

    return T;
}

// 从二叉排序树 T 中删除关键字等于 key 的结点，返回删除结点后树的根结点
BSTree Delete(BSTree T, KeyType key) {
    BSTNode *curr = T, *parent = NULL;
    while (curr) {
        if (key == curr->key) break;
        parent = curr;  // 记录结点 curr 的双亲结点
        if (key < curr->key) curr = curr->left;
        else curr = curr->right;
    }
    // 找不到要删除的结点，直接返回
    if (!curr) return T;

    BSTNode *p = curr;
    if (!curr->left) {  // 要删除的结点没有左子树，包含了左右子树都为空的情况
        curr = curr->right;
    } else if (!curr->right) { // 要删除的结点没有右子树，但是有左子树
        curr = curr->left;
    } else {     // 既有左子树，又有右子树
        // 在 curr 的左子树中继续查找其前驱结点，即最右下结点
        BSTNode *prev = curr->left;
        parent = curr;  // 前驱结点的双亲结点
        while (prev->right) {
            parent = prev;
            prev = prev->right;
        }

        // 将 prev 指向的前驱结点的键值对，覆盖要删除结点的键值对
        curr->key = prev->key;
        curr->value = prev->value;

       // 删除 prev 结点 （前驱结点 prev 没有右子树）
       curr = prev->left;

       p = prev;
    }

    free(p);

    if (!parent) return curr;
    // 将 curr 的孩子上升到 curr 的位置
    if (curr == parent->left) parent->left = curr;
    else parent->right = curr;

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