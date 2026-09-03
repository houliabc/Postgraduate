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
    // 迭代解法
    vector<int> preorderTraversal1(TreeNode* root) {
        if (!root) return {};

        vector<int> res;
        stack<TreeNode*> s;
        s.push(root);
        while (!s.empty()) {
            TreeNode *curr = s.top();
            s.pop();

            res.push_back(curr->val);

            if (curr->right) s.push(curr->right);
            if (curr->left) s.push(curr->left);
        }

        return res;
    }

    // 递归解法
    vector<int> preorderTraversal(TreeNode* root) {
        if (!root) return {};
        vector<int> res;
        preOrder(root, res);
        return res;
    }

    void preOrder(TreeNode* node, vector<int>& res) {
        if (!node) return;

        res.push_back(node->val);

        preOrder(node->left, res);
        preOrder(node->right, res);
    }
};