// Question:
// You are given an array nums consisting of n prime integers.
//
// Construct an array ans of length n such that for every index i:
//     ans[i] OR (ans[i] + 1) == nums[i]
//
// Among all possible values, ans[i] should be minimized.
// If it is not possible to find such a value, set ans[i] = -1.
//
// Return the resulting array ans.

class Solution {
    public int[] minBitwiseArray(int[] nums) {
        int n = nums.length;
        int[] ans = new int[n];

        for (int i = 0; i < n; i++) {
            int x = nums[i];
            int value = -1;

            // Try all possible candidates starting from the smallest
            // ans[i] must be strictly less than nums[i]
            for (int a = 0; a < x; a++) {
                if ((a | (a + 1)) == x) {
                    value = a;
                    break;
                }
            }

            ans[i] = value;
        }

        return ans;
    }
}

/*
Explanation:
- For each prime number x = nums[i], we search for the smallest integer a
  such that a OR (a + 1) equals x.
- The bitwise OR operation can only turn bits on, not off,
  so a must be less than x.
- We brute-force all values from 0 to x - 1 and check the condition.
- The first valid a found is the minimum possible value.
- If no such value exists, we assign -1.
- This approach is efficient because nums[i] ≤ 1000 and nums.length ≤ 100.

Time Complexity:
O(n * max(nums))

Space Complexity:
O(n)
*/
