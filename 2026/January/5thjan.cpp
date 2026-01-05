// Question:
// You are given an n x n integer matrix.
// You can perform the following operation any number of times:
// - Choose any two adjacent elements of the matrix and multiply each of them by -1.
//   (Two elements are adjacent if they share a border.)
//
// Your goal is to maximize the sum of the matrix's elements.
// Return the maximum possible sum after applying the operations optimally.

#include <vector>
#include <climits>
using namespace std;

class Solution {
public:
    long long maxMatrixSum(vector<vector<int>>& matrix) {
        long long totalSum = 0;
        int minAbs = INT_MAX;
        int negativeCount = 0;

        for (auto& row : matrix) {
            for (int val : row) {
                totalSum += abs(val);
                minAbs = min(minAbs, abs(val));
                if (val < 0) {
                    negativeCount++;
                }
            }
        }

        // If number of negative elements is even,
        // all values can be made positive
        if (negativeCount % 2 == 0) {
            return totalSum;
        }

        // If odd, one smallest absolute value must remain negative
        return totalSum - 2LL * minAbs;
    }
};


// Explanation:
// Flipping two adjacent elements changes both of their signs,
// so the parity of the number of negative elements is invariant.
//
// Steps:
// 1) Convert all values to absolute values and sum them.
// 2) Count how many negatives exist initially.
// 3) Track the smallest absolute value in the matrix.
//
// Case 1: Even number of negatives
// - All can be flipped to positive using valid operations.
//
// Case 2: Odd number of negatives
// - Exactly one element must stay negative.
// - To minimize loss, keep the smallest absolute value negative.
//
// Time Complexity: O(n^2)
// Space Complexity: O(1)
// Time Complexity: O(n * sqrt(m)), where n is the number of elements in nums and m is the maximum value in nums.