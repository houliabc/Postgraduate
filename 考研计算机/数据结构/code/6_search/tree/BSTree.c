#include <stdio.h>
#include <string.h>

#include "BSTree.h"

// 获取键 key 对应的值（若 key 不存在，则返回 NULL）
// 时间复杂度：O(h)
ValueType Get(BSTree T, KeyType key) {
    BSTNode *curr = T;
    while (curr) {
        if (key == curr->key) return curr->value;
        else if (key < curr->key) curr = curr->left;
        else curr = curr->right;
    }
    return NULL;
}

// 将键值对存入表中，并返回 BST 的根结点
// 时间复杂度：O(h)
BSTree Put(BSTree T, KeyType key, ValueType value) {
    BSTNode *curr = T;
    BSTree parent = NULL;
    while (curr) {
        parent = curr;
        if (key == curr->key) {
            curr->value = strdup(value);
            return T;
        } else if (key < curr->key) curr = curr->left;
        else curr = curr->right;
    }

    // 创建新节点
    BSTNode *newNode = CreateNode(key, value);

    // 如果树为空，新节点就是根节点
    if (!parent) return newNode;

    // 插入新节点作为父节点的左子节点或右子节点
    if (key < parent->key) parent->left = newNode;
    else parent->right = newNode;

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
        if (!parent) { // 删除的是根结点的话
            free(p);
            return curr;
        }
    } else if (!curr->right) { // 要删除的结点没有右子树，但是有左子树
        curr = curr->left;
        if (!parent) { // 删除的是根结点的话
            free(p);
            return curr;
        }
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

    // 将 curr 的孩子上升到 curr 的位置
    if (p == parent->left) parent->left = curr;
    else parent->right = curr;

    free(p);

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