// Question:
// Given the root of a binary tree, the depth of each node is the shortest
// distance to the root.
//
// Return the smallest subtree such that it contains all the deepest nodes
// in the original tree.
//
// A node is called the deepest if it has the largest depth in the tree.
// The subtree of a node consists of that node and all its descendants.

class Solution {
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        return dfs(root).second;
    }

    // Returns a pair of (depth, subtree_root)
    pair<int, TreeNode*> dfs(TreeNode* node) {
        if (!node) {
            return {0, nullptr};
        }

        auto left = dfs(node->left);
        auto right = dfs(node->right);

        // If left subtree is deeper, propagate its result
        if (left.first > right.first) {
            return {left.first + 1, left.second};
        }

        // If right subtree is deeper, propagate its result
        if (right.first > left.first) {
            return {right.first + 1, right.second};
        }

        // If both depths are equal, current node is the answer
        return {left.first + 1, node};
    }
};


// Explanation:
// We use a bottom-up Depth-First Search.
//
// For each node, DFS returns:
// - The maximum depth reachable from this node
// - The root of the smallest subtree that contains all deepest nodes below it
//
// Logic at each node:
// - If left depth > right depth → deepest nodes are in the left subtree
// - If right depth > left depth → deepest nodes are in the right subtree
// - If both depths are equal → deepest nodes exist on both sides,
//   so the current node is their lowest common ancestor
//
// This ensures we return the smallest subtree that contains all deepest nodes.
//
// Time Complexity: O(n)
// Space Complexity: O(n) due to recursion stack