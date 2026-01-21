// Question:
// You are given an array nums consisting of n prime integers.
//
// Construct an array ans of length n such that for each index i:
//     ans[i] OR (ans[i] + 1) == nums[i]
//
// Minimize ans[i]. If no such value exists, set ans[i] = -1.
//
// Return the resulting array.

class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);

        for (int i = 0; i < n; i++) {
            int x = nums[i];

            // If x is even, impossible
            if ((x & 1) == 0) {
                ans[i] = -1;
                continue;
            }

            // Count trailing 1s in x
            int t = 0;
            while (((x >> t) & 1) == 1) {
                t++;
            }

            // Remove the highest bit among trailing 1s
            ans[i] = x - (1 << (t - 1));
        }

        return ans;
    }
};

/*
Explanation:
- For x = a | (a + 1) to hold, x must be odd.
- Let x end with k trailing 1s in binary.
- The smallest valid a is obtained by clearing the highest bit
  among those trailing 1s:
      a = x - 2^(k-1)
- This guarantees:
      a OR (a + 1) == x
  and a is minimized.
- If x is even, no such a exists.

Time Complexity:
O(n · log(nums[i]))

Space Complexity:
O(n)
*/
