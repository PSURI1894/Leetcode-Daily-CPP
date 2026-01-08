// Question:
// Given two integer arrays nums1 and nums2.
//
// Return the maximum dot product between non-empty subsequences of nums1 and nums2
// that have the same length.
//
// A subsequence is formed by deleting some (or none) elements without changing
// the order of the remaining elements.
//
// The dot product of two arrays of equal length is the sum of the products of
// corresponding elements.

#include <vector>
#include <climits>
using namespace std;

class Solution {
public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int m = nums2.size();

        // dp[i][j] = maximum dot product using nums1[i:] and nums2[j:]
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, INT_MIN));

        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                int product = nums1[i] * nums2[j];

                // Option 1: take nums1[i] and nums2[j] as a new subsequence
                int takeBoth = product;

                // Option 2: extend an existing subsequence if it helps
                if (dp[i + 1][j + 1] > 0) {
                    takeBoth = product + dp[i + 1][j + 1];
                }

                // Option 3: skip one element
                int skipNums1 = dp[i + 1][j];
                int skipNums2 = dp[i][j + 1];

                dp[i][j] = max(takeBoth, max(skipNums1, skipNums2));
            }
        }

        return dp[0][0];
    }
};


// Explanation:
// This problem is solved using Dynamic Programming.
//
// Core difficulty:
// - Subsequences must be non-empty
// - Values can be negative, so we cannot initialize dp with 0
//
// State Definition:
// dp[i][j] stores the maximum dot product that can be achieved
// using nums1 starting from index i and nums2 starting from index j.
//
// Transitions at (i, j):
// 1) Pair nums1[i] with nums2[j]:
//    - Start a new subsequence: nums1[i] * nums2[j]
//    - Or extend an existing one if dp[i+1][j+1] is positive
//
// 2) Skip nums1[i]:
//    dp[i+1][j]
//
// 3) Skip nums2[j]:
//    dp[i][j+1]
//
// We take the maximum of all choices.
//
// Initialization:
// dp is initialized with INT_MIN to enforce picking at least one pair.
//
// Final Answer:
// dp[0][0] gives the maximum dot product for the full arrays.
//
// Time Complexity: O(n * m)
// Space Complexity: O(n * m)
