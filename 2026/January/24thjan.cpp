// Question:
// 1877. Minimize Maximum Pair Sum in Array
//
// The pair sum of a pair (a, b) is equal to a + b.
// Given an array nums of even length n, pair up the elements into n/2 pairs such that:
// 1. Each element is used exactly once.
// 2. The maximum pair sum among all pairs is minimized.
//
// Return the minimized maximum pair sum.

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minPairSum(vector<int>& nums) {
        // Sort the array to apply greedy pairing
        sort(nums.begin(), nums.end());

        int left = 0;
        int right = nums.size() - 1;
        int maxPairSum = 0;

        // Pair smallest with largest
        while (left < right) {
            maxPairSum = max(maxPairSum, nums[left] + nums[right]);
            left++;
            right--;
        }

        return maxPairSum;
    }
};

/*
Explanation:

Core Idea:
To minimize the maximum pair sum, we must avoid pairing large numbers together.
The optimal greedy strategy is:
- Sort the array
- Pair the smallest element with the largest element

Why this works:
- If two large numbers are paired together, their sum becomes very large.
- Pairing smallest with largest balances all pair sums.
- This guarantees the smallest possible maximum among all pairs.

Example:
nums = [3,5,2,3]
Sorted = [2,3,3,5]

Pairs formed:
(2,5) -> 7
(3,3) -> 6

Maximum pair sum = 7 (minimum achievable)

Time Complexity: O(n log n) due to sorting
Space Complexity: O(1) extra space (ignoring sort internals)
*/
