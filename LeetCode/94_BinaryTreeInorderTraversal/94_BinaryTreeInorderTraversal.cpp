#include <iostream>
#include <vector>
using namespace std;

/* https://leetcode.com/explore/learn/card/queue-stack/232/practical-application-stack/1383/
https://leetcode.com/problems/binary-tree-inorder-traversal

PROBLEM: Given the root of a binary tree, return the inorder traversal of its nodes' values.

Example 1:
Input: root = [1,null,2,3]
Output: [1,3,2]

Example 2:

Input: root = []
Output: []

Example 3:

Input: root = [1]
Output: [1]


CONSTRAINTS:
    The number of nodes in the tree is in the range [0, 100].
    -100 <= Node.val <= 100
*/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        dfs(result, root);
        return result;
    }
private:
    void dfs(vector<int>& v, TreeNode* root) {
        if (root == NULL) return;
        dfs(v, root->left);
        v.push_back(root->val);
        dfs(v, root->right);
        return;
    }
};

//helper
void print(const vector<int>& v) {
    for (auto it = v.begin(); it != v.end(); it++) {
        cout << *it << endl;
    }
}

int main()
{
    Solution s;
    TreeNode* root = new TreeNode(1, NULL, new TreeNode(2, new TreeNode(3, NULL, NULL), NULL));
    print(s.inorderTraversal(root));


}