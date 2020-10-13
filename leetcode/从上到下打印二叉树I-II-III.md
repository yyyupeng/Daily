/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// I
    class Solution {
    public:
    vector<int> levelOrder(TreeNode* root) {
        if(!root)   return vector<int> ();
        vector<int> res;
        queue<TreeNode *> q;
        q.push(root);
        while(!q.empty())
        {
            TreeNode *temp = q.front();
            q.pop();
            res.push_back(temp->val);
            if(temp->left)
                q.push(temp->left);
            if(temp->right)
                q.push(temp->right);
        }
        return res;
    }
    };
    
// II
    class Solution {
    public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if(!root)   return {};
        vector<vector<int>> res;
        queue<TreeNode *> q;
        q.push(root);
        while(!q.empty())
        {
            int size = q.size();
            vector<int> temp;
            for(int i = 0; i < size; ++i)
            {
                TreeNode *tmp = q.front();
                q.pop();
                temp.push_back(tmp->val);
                if(tmp->left)
                    q.push(tmp->left);
                if(tmp->right)
                    q.push(tmp->right);
            }
            if(!temp.empty())
                res.push_back(temp);
        }
        return res;
    }
    };

// III
    class Solution {
    public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if(!root)   return {};
        vector<vector<int>> res;
        deque<TreeNode *> q;
        q.push_back(root);
        int n = 1;
        while(!q.empty())
        {
            int size = q.size();
            vector<int> temp;
            for(int i = 0; i < size; ++i)
            {
                if(n & 1)   //奇数层
                {
                    TreeNode *tmp = q.back();
                    q.pop_back();
                    temp.push_back(tmp->val);
                    if(tmp->left)
                        q.push_front(tmp->left);
                    if(tmp->right)
                        q.push_front(tmp->right);
                }
                else    //偶数层
                {
                    TreeNode *tmp = q.front();
                    q.pop_front();
                    temp.push_back(tmp->val);
                    if(tmp->right)
                        q.push_back(tmp->right);
                    if(tmp->left)
                        q.push_back(tmp->left);
                }
            }
            n++;
            if(!temp.empty())
                res.push_back(temp);
        }
        return res;
    }
    };
