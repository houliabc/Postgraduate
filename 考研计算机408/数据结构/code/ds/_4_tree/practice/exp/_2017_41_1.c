#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// 二叉树结点定义
typedef struct node {
    // 存储操作数或操作符
    char data[10];
    struct node *left, *right;
} BTree;

// 将表达式树转换为中缀表达式的函数
void TreeToInfix(BTree* root, BTree *parent) {
    if (root == NULL) return;

    // 当前结点是叶子结点，直接打印元素值
    if (!root->left && !root->right) {
        printf("%s", root->data);
        return;
    }

    // 在遍历左子树之前，加上左括号 
    if (parent) printf("(");
    // 递归处理左子树
    TreeToInfix(root->left, root);
    // 当左子树遍历完，打印当前结点元素
    printf("%s", root->data);
    // 递归处理右子树
    TreeToInfix(root->right, root);
    // 在遍历完右子树之后，加上右括号
    if (parent) printf(")"); 
}

// 辅助函数，用于创建新的二叉树节点
BTree* newNode(char* data) {
    BTree* node = (BTree*)malloc(sizeof(BTree));
    strcpy(node->data, data);
    node->left = NULL;
    node->right = NULL;
    return node;
}

int main() {

    // 构造示例表达式树 1: (* (+ a b) (* c (- d)))
    BTree* root1 = newNode("*");
    root1->left = newNode("+");
    root1->left->left = newNode("a");
    root1->left->right = newNode("b");
    root1->right = newNode("*");
    root1->right->left = newNode("c");
    root1->right->right = newNode("-");
    root1->right->right->right = newNode("d");

    TreeToInfix(root1, NULL);

    return 0;
}