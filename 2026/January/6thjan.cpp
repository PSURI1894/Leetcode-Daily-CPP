// Question:
// Given the root of a binary tree, the level of its root is 1,
// the level of its children is 2, and so on.
//
// Return the smallest level x such that the sum of all the values
// of nodes at level x is maximum.

#include <queue>
using namespace std;

class Solution {
public:
    int maxLevelSum(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);

        int level = 1;
        int answerLevel = 1;
        long long maxSum = LLONG_MIN;

        while (!q.empty()) {
            int size = q.size();
            long long levelSum = 0;

            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();
                levelSum += node->val;

                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }

            if (levelSum > maxSum) {
                maxSum = levelSum;
                answerLevel = level;
            }

            level++;
        }

        return answerLevel;
    }
};


// Explanation:
// We perform a level-order traversal (BFS) using a queue.
//
// For each level of the tree:
// - Sum the values of all nodes at that level.
// - If this sum is greater than the maximum sum seen so far,
//   update the maximum sum and record the current level.
//
// Because levels are processed from top to bottom,
// the first level with the maximum sum is automatically selected.
//
// Time Complexity: O(n)
// Space Complexity: O(n)
