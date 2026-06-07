#include <stdlib.h>
#include <stdio.h>

// 定义二叉树结点结构
typedef struct TreeNode {
    char c;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode, *BTree;

// 创建新结点
TreeNode* createNode() {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 释放二叉树内存
void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// 根据每个字符的前缀编码生成相应的前缀二叉树
// characters: 字符
// codes: 字符对应的前缀编码
BTree GenPrefixTree(char *characters, int n, char *codes[n]) {
    // 首先创建根结点
    TreeNode *root = createNode();

    for (int i = 0; i < n; i++) {
        // 当前编码
        const char* code = codes[i];

        TreeNode* curr = root;
        for (int j = 0; code[j] != '\0'; j++) {
            if (code[j] == '0') { // 走左分支
                if (!curr->left) curr->left = createNode();
                curr = curr->left;
            } else if (code[j] == '1') { // 走右分支
                if (!curr->right) curr->right = createNode();
                curr = curr->right;
            }
        }

        // 设置叶子结点的字符
        curr->c = characters[i];
    }

    return root;
}

// 解压缩（译码）
// root: 前缀二叉树
// data: 0/1 串
void Decode(BTree root, char *data) {
    TreeNode* curr = root;
    for (int i = 0; data[i] != '\0'; i++) {
        if (data[i] == '0') {   // 走左分支
            curr = curr->left;
        } else if (data[i] == '1') { // 走右分支
            curr = curr->right;
        }

        // 判断当前结点是叶子结点，则打印字符，并且从根结点重新开始
        if (!curr->left && !curr->right) {
            printf("%c", curr->c);
            curr = root;
        }
    }
}

int main() {
    char characters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    char* codes[] = {"0100", "10", "0000", "0101", "001", "011", "11", "0001"};
    

    BTree root = GenPrefixTree(characters, 8, codes);

    Decode(root, "0100011001001011110101");
    
    free(root);
    return 0;
}