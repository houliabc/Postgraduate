#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

int GetHeight(AVLTNode *node) {
    if (!node) return 0;
    return node->height;
}

int GetBalanceFactor(AVLTNode *node) {
    if (!node) return 0;
    return GetHeight(node->left) - GetHeight(node->right);
}

ValueType Get(AVLTree T, KeyType key) {
    if (!T) return NULL;
    if (T->key == key)
        return T->value;
    else if (key < T->key) return Get(T->left, key);
    else return Get(T->right, key);
    return NULL;
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
    y->right = x->left;
    x->left = y;

    // 更新x和y的高度
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
    y->left = x->right;
    x->right = y;

    // 更新x和y的高度
    y->height = max(GetHeight(y->left), GetHeight(y->right)) + 1;
    x->height = max(GetHeight(x->left), GetHeight(x->right)) + 1;
    return x;
}

// 在二叉排序树 T 中，插入指定键值对，并返回插入了结点后的 BST 的根结点
// 时间复杂度：O(logn)
// 空间复杂度：O(logn)
AVLTree Put(AVLTree T, KeyType key, ValueType value) {
    // 先找到位置继续插入
    // 空树直接返回
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

    // 插入完后关键在于调整平衡二叉树，以及返回新的根（还需要更新树高，平衡因子）
    T->height = max(GetHeight(T->left), GetHeight(T->right)) + 1;
    int bf = GetBalanceFactor(T);
    // LL
    if (bf > 1 && GetBalanceFactor(T->left) >= 0) {
        return RightRotate(T);
    }
    // LR
    if (bf > 1 && GetBalanceFactor(T->left) < 0) {
        T->left = LeftRotate(T->left);
        return RightRotate(T);
    }
    // RR
    if (bf < -1 && GetBalanceFactor(T->right) < 0) {
        return LeftRotate(T);
    }
    // RL
    if (bf < -1 && GetBalanceFactor(T->right) > 0) {
        T->right = RightRotate(T->right);
        return LeftRotate(T);
    }
    return T;
}