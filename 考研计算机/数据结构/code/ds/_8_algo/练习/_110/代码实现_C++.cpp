/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool isBalanced(TreeNode* root) {
         return maxDepth(root) >= 0;
    }

    // DFS 后序遍历 - 递归
    int maxDepth(TreeNode* root) {
        if (!root) return 0;

        int leftMaxDepth = maxDepth(root->left);
        int rightMaxDepth = maxDepth(root->right);

        if (leftMaxDepth == -1 ||
                rightMaxDepth == -1 ||
                abs(leftMaxDepth - rightMaxDepth) > 1)
            return -1;

        return max(leftMaxDepth, rightMaxDepth) + 1;
    }
};