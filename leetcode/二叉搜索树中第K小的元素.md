给定一个二叉搜索树，编写一个函数 kthSmallest 来查找其中第 k 个最小的元素。
说明：
你可以假设 k 总是有效的，1 ≤ k ≤ 二叉搜索树元素个数。

示例 1:
输入: root = [3,1,4,null,2], k = 1
   3
  / \
 1   4
  \
   2
输出: 1

示例 2:
输入: root = [5,3,6,2,4,null,null,1], k = 3
       5
      / \
     3   6
    / \
   2   4
  /
 1
输出: 3

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
    int kthSmallest(TreeNode* root, int k) {
        //中序遍历
        stack<TreeNode *> s;
        TreeNode *temp = nullptr;
        while(root || !s.empty())
        {
            if(root)
            {
                s.push(root);
                root = root->left;
            }
            else
            {
                k--;
                temp = s.top();
                s.pop();
                if(k == 0)
                    break;
                root = temp->right;
            }
        }
        return temp->val;
    }
    };
