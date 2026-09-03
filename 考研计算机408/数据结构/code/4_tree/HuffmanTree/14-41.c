#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// （1）初始化WPL的值为0，递归先序遍历T中的每个结点，遍历根节点时，路径长度传入为0，当每递归遍历左子树或右子树时，将路径长度+1作为参数传进递归函数中。当当前结点为叶子节点时，将路径长度与权值的乘积累加到WPL当中。当二叉树遍历完后返回WPL值。
// （2）
typedef int ElemType;
typedef struct bNode {
    struct bNode *left, *right;
    ElemType weight;
} BTree;
// （3）
int wpl = 0;  // 全局遍历用来计算WPL
int getWPL(BTree *root, int pathNum) {
    // 空数
    if (!root)
        return 0;
    // 若是叶子节点
    if (!root->left && !root->right) {
        // 结点的路径长度和权值乘积
        return root->weight * pathNum;
    }
    // 否则递归遍历左右子树，且将路径长度加一
    wpl += getWPL(root->left, pathNum + 1);
    wpl += getWPL(root->right, pathNum + 1);
    return wpl;
}

int main() {
    
    return 0;
}