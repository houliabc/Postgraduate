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

// 获取运算符优先级的函数
int getPrecedence(char* op) {
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0)
        return 1;
    if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0)
        return 2;
    return 0; // 操作数或其他情况
}

// 判断是否需要添加括号的函数，参数是双亲节点和其孩子结点
bool needParentheses(BTree* parent, BTree* child) {
    // 根结点不需要加括号，只有根没有双亲结点
    if (!parent) return false;

    // 叶子节点不需要括号
    if (!child->left && !child->right)
        return false; 

    // 拿到父结点和子结点的运算符的优先级
    int parentPrecedence = getPrecedence(parent->data);
    int childPrecedence = getPrecedence(child->data);

    // 子节点优先级低于父节点需要括号
    if (childPrecedence < parentPrecedence) return true;

    // 同级运算符处理
    if (childPrecedence == parentPrecedence) {
        // 如果当前结点是双亲的左孩子，不需要加括号
        if (child == parent->left) return false;
        else return true;   // 如果当前结点是双亲结点的右孩子，则需要加括号
    }

    // 子节点优先级高于父节点不需要括号
    return false; 
}

// 将表达式树转换为中缀表达式的函数
void TreeToInfix(BTree* root, BTree *parent) {
    if (root == NULL) return;

    // 判断是否需要打印左右括号
    int shouldAddParens = needParentheses(parent, root);

    // 在遍历左子树之前，加上左括号 
    if (shouldAddParens) printf("(");
    // 递归处理左子树
    TreeToInfix(root->left, root);
    // 当左子树遍历完，打印当前结点元素
    printf("%s", root->data);
    // 递归处理右子树
    TreeToInfix(root->right, root);
    // 在遍历完右子树之后，加上右括号
    if (shouldAddParens) printf(")"); 
}

// 辅助函数，用于创建新的二叉树节点
BTree* newNode(char* data) {
    BTree* node = (BTree*)malloc(sizeof(BTree));
    strcpy(node->data, data);
    node->left = NULL;
    node->right = NULL;
    return node;
}

/*
int main() {
    // 构造对应测试用例的表达式树
    BTree* root = newNode("+");
    root->left = newNode("+");
    root->left->left = newNode("a");
    root->left->right = newNode("+");
    root->left->right->left = newNode("-");
    root->left->right->left->right = newNode("b");
    root->left->right->right = newNode("c");

    root->right = newNode("d");

    TreeToInfix(root, NULL);

    return 0;
}
*/


int main() {
    // 构造对应测试用例的表达式树
    BTree* root = newNode("+");
    root->left = newNode("*");
    root->left->left = newNode("a");
    root->left->right = newNode("b");

    root->right = newNode("-");
    root->right->right = newNode("-");
    root->right->right->left = newNode("c");
    root->right->right->right = newNode("d");

    TreeToInfix(root, NULL);

    return 0;
}

/*
int main() {
    // 构造对应测试用例的表达式树
    BTree* subNode1 = newNode("-");
    subNode1->left = newNode("c");
    subNode1->right = newNode("d");

    BTree* subNode2 = newNode("*");
    subNode2->left = newNode("b");
    subNode2->right = subNode1;

    BTree* subNode3 = newNode("+");
    subNode3->left = newNode("a");
    subNode3->right = subNode2;

    BTree* subNode4 = newNode("/");
    subNode4->left = newNode("e");
    subNode4->right = newNode("f");

    BTree* root = newNode("-");
    root->left = subNode3;
    root->right = subNode4;

    TreeToInfix(root, NULL);

    return 0;
}*/