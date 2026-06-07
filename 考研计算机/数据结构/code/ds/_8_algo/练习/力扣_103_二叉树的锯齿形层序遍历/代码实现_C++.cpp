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
    // BFS
    vector<vector<int>> zigzagLevelOrder1(TreeNode* root) {
        if (root == NULL) return {};

        vector<vector<int> > res;

        queue<TreeNode*> q;
        q.push(root);
        bool fromRight = false;

        while (!q.empty()) {
            int size = q.size();
            // 因为我们已经知道了这一层有多少个节点，所以可以固定大小
            vector<int> row(size);
            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();
                // 如果是从右往左的话，那么将节点值从后往前放，否则从前往后放
                int index = fromRight ? (size - 1 - i) : i;
                row[index] = node->val;

                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            res.push_back(row);
            fromRight = !fromRight;
        }
        return res;
    }
};