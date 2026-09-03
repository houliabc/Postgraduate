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
    vector<int> postorderTraversal1(TreeNode* root) {
        if (!root) return {};

        vector<int> res;
        stack<TreeNode*> s;
        s.push(root);
        while (!s.empty()) {
            TreeNode *curr = s.top();
            res.push_back(curr->val);
            s.pop();
            if (curr->left) s.push(curr->left);
            if (curr->right) s.push(curr->right);
        }
        reverse(res.begin(), res.end());
        return res;
    }

    // 递归解法
    vector<int> postorderTraversal(TreeNode* root) {
        if (!root) return {};
        vector<int> res;
        postorder(root, res);
        return res;
    }

    void postorder(TreeNode* node, vector<int>& res) {
        if (!node) return;
        postorder(node->left, res);
        postorder(node->right, res);
        res.push_back(node->val);
    }
};