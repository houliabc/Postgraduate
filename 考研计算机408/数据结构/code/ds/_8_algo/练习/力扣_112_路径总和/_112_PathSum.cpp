/**
* 抖码算法，让算法学习变的简单有趣
* @作者 : 老汤
*/

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : val(val), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) return false;

        if (root->left == nullptr && root->right == nullptr) {
            return targetSum - root->val == 0;
        }

        int leftHasPathSum = hasPathSum(root->left, targetSum - root->val);
        if (leftHasPathSum) return true;

        int rightHasPathSum = hasPathSum(root->right, targetSum - root->val);

        return leftHasPathSum || rightHasPathSum;
    }
};