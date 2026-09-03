#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

typedef int KeyType;
typedef char* ValueType;

// 二叉树排序树结点
typedef struct node {
    KeyType key;        // 关键字
    ValueType value;    // 值
    int height;         // 结点的高度
    struct node *left;  // 左孩子指针
    struct node *right; // 右孩子指针
} AVLTNode, *AVLTree;

// 创建新结点
AVLTNode *CreateNode(KeyType key, ValueType value) {
    AVLTNode *newNode = (AVLTNode *) malloc (sizeof(AVLTNode));
    newNode->key = key;
    newNode->value = value;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 销毁平衡二叉树
void DestroyAVLTree(AVLTree T) {
    if (!T) return;

    DestroyAVLTree(T->left);
    DestroyAVLTree(T->right);
    free(T);
} 

// 拿到指定结点的高度
int GetHeight(AVLTNode *node) {
    if (!node) return 0;    // 空结点的高度为 0
    return node->height;
}

// 拿到指定结点的平衡因子
int GetBalanceFactor(AVLTNode *node) {
    if (!node) return 0;    // 空结点的平衡因子为 0
    // 平衡因子等于左右子节点的高度差
    return GetHeight(node->left) - GetHeight(node->right);
}

// 在二叉查找树 T 中，查找并返回关键字 key 对应的 value
// 时间复杂度：O(logn)
// 空间复杂度：O(logn)
ValueType Get(AVLTree T, KeyType key) {
    if (!T) return NULL;
    if (key == T->key) return T->value;
    else if (key < T->key) return Get(T->left, key);
    else return Get(T->right, key);
}

/* 
对节点 y 进行向左旋转操作，返回旋转后新的根节点 x
    y                             x
  /  \                          /   \
 T3   x      向左旋转 (y)       y    T1
     / \   - - - - - - - ->   / \  
    T2 T1                    T3 T2
*/
AVLTNode *LeftRotate(AVLTNode *y) {
    AVLTNode *x = y->right;
    AVLTNode *t2 = x->left;

    // 左旋转
    x->left = y;
    y->right = t2;

    // 更新 x 和 y 的高度
    // 必须先要计算 y 节点的高度，然后才计算 x 节点的高度
    // 原因：上面的 x.left = y ，说明 y 是 x 的子结点，需要先计算子结点的高度，才能计算父结点高度
    y->height = max(GetHeight(y->left), GetHeight(y->right)) + 1;
    x->height = max(GetHeight(x->left), GetHeight(x->right)) + 1;

    return x;
}

/* 对节点 y 进行向右旋转操作，返回旋转后新的根节点 x
        y                                    x
       / \                                 /   \
      x   T3        向右旋转 (y)          T1     y
     / \          --------------->              / \
    T1 T2                                     T2   T3
 */
AVLTNode *RightRotate(AVLTNode *y) {
    AVLTNode *x = y->left;
    AVLTNode *t2 = x->right;

    // 右旋转
    x->right = y;
    y->left = t2;

    // 更新 x 和 y 的高度
    // 必须先要计算 y 节点的高度，然后才计算 x 节点的高度
    // 原因：上面的 x.right = y ，说明 y 是 x 的子节点，需要先计算子节点的高度，才能计算父节点高度
    y->height = max(GetHeight(y->left), GetHeight(y->right)) + 1;
    x->height = max(GetHeight(x->left), GetHeight(x->right)) + 1;

    return x;
}

// 在二叉排序树 T 中，插入指定键值对，并返回插入了结点后的 BST 的根结点
// 时间复杂度：O(logn)
// 空间复杂度：O(logn)
AVLTree Put(AVLTree T, KeyType key, ValueType value) {
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

    // 更新父亲节点的高度值
    // 父亲节点的高度值等于左右子节点最大的高度值再加上 1
    T->height = max(GetHeight(T->left), GetHeight(T->right)) + 1;

    // 计算每个父亲节点的平衡因子
    int bf = GetBalanceFactor(T);

    // RR
    if (bf < -1 && GetBalanceFactor(T->right) < 0) {
        return LeftRotate(T);
    }

    // RL
    if (bf < -1 && GetBalanceFactor(T->right) > 0) {
        // 先将 T->right 进行右旋，转成 RR
        T->right = RightRotate(T->right);
        // 然后对 T 进行左旋
        return LeftRotate(T);
    }

    // LL
    if (bf > 1 && GetBalanceFactor(T->left) >= 0) {
        return RightRotate(T);
    }

    // LR
    if (bf > 1 && GetBalanceFactor(T->left) < 0) {
        // 先将 T->left 进行左旋，转成 LL
        T->left = LeftRotate(T->left);
        // 然后对 T 进行右旋
        return RightRotate(T);
    }

    return T;
}