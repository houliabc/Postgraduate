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
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root) return {};

        vector<vector<int>> res;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int size = q.size();
            vector<int> levelNodes;
            for (int i = 0; i < size; i++) {
                TreeNode *curr = q.front();
                q.pop();
                levelNodes.push_back(curr->val);
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
            res.push_back(levelNodes);
        }

        return res;
    }

    // 前序遍历 + 迭代
    vector<vector<int>> levelOrder2(TreeNode* root) {
        if (!root) return {};

        vector<vector<int>> res;
        stack<pair<TreeNode*, int>> s;
        s.push(make_pair(root, 0));
        while (!s.empty()) {
            pair<TreeNode*, int> curr = s.top();
            s.pop();
            TreeNode *currNode = curr.first;
            int currLevel = curr.second;

            if (res.size() == currLevel) {
                vector<int> levelNodes = {currNode->val};
                res.push_back(levelNodes);
            } else {
                res[currLevel].push_back(currNode->val);
            }

            if (currNode->right) s.push(make_pair(currNode->right, currLevel + 1));
            if (currNode->left) s.push(make_pair(currNode->left, currLevel + 1));
        }

        return res;
    }

    // 前序遍历 + 递归
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root) return {};

        vector<vector<int>> res;
        preOrder(root, 0, res);
        return res;
    }

    void preOrder(TreeNode* node, int currLevel, vector<vector<int>>& res) {
        if (!node) return;

        if (res.size() == currLevel) {
            vector<int> levelNodes = {node->val};
            res.push_back(levelNodes);
        } else {
            res[currLevel].push_back(node->val);
        }

        preOrder(node->left, currLevel + 1, res);
        preOrder(node->right, currLevel + 1,  res);
    }
};