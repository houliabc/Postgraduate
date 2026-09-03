#include <stdio.h>

typedef struct BiTNode {
    int weight;
    struct BiTNode *left;
    struct BiTNode *right;
} BiTNode, *BTree;

// 计算以 node 为根节点的二叉树的带权路径长度，并返回
int PostOrder(BiTNode *node, int pathLen) {
    // 空树的带权路径长度为 0
    if (!node) return 0;

    // 叶子结点的带权路径长度为其权值和路径长度的乘积
    if (!node->left && !node->right) {
        return node->weight * pathLen;
    }

    // 递归的去计算左子树的带权路径长度
    int leftWPL = PostOrder(node->left, pathLen + 1);
    // 递归的去计算右子树的带权路径长度
    int rightWPL = PostOrder(node->right, pathLen + 1);

    // 以 node 为根的子树的带权路径长度等于左右子树的带权路径长度之和
    return leftWPL + rightWPL;
}

// 计算二叉树 root 的带权路径长度
int WPL(BTree root) {
    return PostOrder(root, 0);
}