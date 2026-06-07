#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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

// 验证编码是否是前缀编码
// characters: 字符
// codes: 字符对应的编码
bool IsValidPrefixCode(char *characters, int n, char *codes[n]) {
    // 首先创建根结点
    TreeNode *root = createNode();

    for (int i = 0; i < n; i++) {
        // 当前编码
        const char* code = codes[i];

        TreeNode* curr = root;
        for (int j = 0; code[j] != '\0'; j++) {
            bool isNewNode = false;
            if (code[j] == '0') { // 走左分支
                if (!curr->left) {
                    curr->left = createNode();
                    isNewNode = true;
                }
                curr = curr->left;
            } else if (code[j] == '1') { // 走右分支
                if (!curr->right) {
                    curr->right = createNode();
                    isNewNode = true;
                }
                curr = curr->right;
            }

            // 如果 curr 不是新创建的，并且 code[j] 不是最后一个字符
            // 并且路径上的结点已经是叶子结点，则违反前缀性质
            // 字符 curr->c 的编码肯定是字符 characters[i] 编码的前缀
            if (!isNewNode && code[j + 1] != '\0' && !curr->left && !curr->right) {
                free(root);
                return false;
            }
        }

        // 设置叶子结点的字符
        curr->c = characters[i];

        // 如果编码最后一位对应结点有子结点，则违反前缀性质
        // characters[i] 编码肯定是其他字符编码的前缀
        if (curr->left || curr->right) {
            freeTree(root);
            return false;
        }
    }

    return true;
}