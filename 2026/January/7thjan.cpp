// Question:
// Given the root of a binary tree, split the binary tree into two subtrees
// by removing exactly one edge such that the product of the sums of the
// two resulting subtrees is maximized.
//
// Return the maximum product of the subtree sums.
// Since the answer may be very large, return it modulo (10^9 + 7).
//
// Note: You must maximize the product before taking the modulo.

#include <climits>
using namespace std;

class Solution {
public:
    long long totalSum = 0;
    long long maxProduct = 0;
    static const int MOD = 1e9 + 7;

    int maxProduct(TreeNode* root) {
        // First DFS to compute total sum of the tree
        totalSum = computeSum(root);

        // Second DFS to compute maximum product
        computeProduct(root);

        return maxProduct % MOD;
    }

    long long computeSum(TreeNode* node) {
        if (!node) return 0;
        return node->val + computeSum(node->left) + computeSum(node->right);
    }

    long long computeProduct(TreeNode* node) {
        if (!node) return 0;

        long long leftSum = computeProduct(node->left);
        long long rightSum = computeProduct(node->right);

        long long currSum = node->val + leftSum + rightSum;

        // Product if we cut the edge above this subtree
        long long product = currSum * (totalSum - currSum);
        maxProduct = max(maxProduct, product);

        return currSum;
    }
};


// Explanation:
// Removing any one edge splits the tree into two parts:
// - one subtree with sum = s
// - the rest of the tree with sum = totalSum - s
//
// The product for this split is:
// s * (totalSum - s)
//
// Steps:
// 1) First DFS calculates the total sum of all nodes.
// 2) Second DFS calculates the sum of every subtree.
//    For each subtree, we compute the product and update the maximum.
// 3) The modulo is applied only once after the maximum product is found.
//
// Time Complexity: O(n)
// Space Complexity: O(n) due to recursion stack
