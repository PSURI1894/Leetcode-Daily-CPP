// Question:
// 1984. Minimum Difference Between Highest and Lowest of K Scores
//
// You are given an integer array nums where nums[i] represents the score
// of the i-th student, and an integer k.
//
// You need to pick scores of any k students such that the difference between
// the highest and the lowest of those k scores is minimized.
//
// Return the minimum possible difference.

#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) {
        // If only one element is chosen, difference is always 0
        if (k == 1) return 0;

        // Sort the array to bring close values together
        sort(nums.begin(), nums.end());

        int n = nums.size();
        int ans = INT_MAX;

        // Sliding window of size k
        for (int i = 0; i + k - 1 < n; i++) {
            int diff = nums[i + k - 1] - nums[i];
            ans = min(ans, diff);
        }

        return ans;
    }
};

/*
Explanation:

Core Idea:
To minimize (maximum - minimum) among k chosen elements,
we should choose k elements that are as close as possible.

Why sorting helps:
- After sorting, the smallest range containing k elements
  will always appear as a contiguous subarray.
- Any scattered selection would only increase the difference.

Algorithm:
1. Sort nums.
2. Use a sliding window of size k.
3. For each window:
      difference = nums[i + k - 1] - nums[i]
4. Track the minimum difference.

Example:
nums = [9,4,1,7], k = 2
Sorted = [1,4,7,9]

Windows:
[1,4] -> diff = 3
[4,7] -> diff = 3
[7,9] -> diff = 2  <-- minimum

Answer = 2

Time Complexity:
O(n log n) due to sorting

Space Complexity:
O(1) extra space (excluding sorting internals)
*/
