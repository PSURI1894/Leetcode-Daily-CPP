// Question:
// You are given an integer array nums.
// Return the sum of divisors of the integers in nums that have exactly four divisors.
// If no such integer exists, return 0.
//
// Example:
// nums = [21, 4, 7]
// 21 has divisors: 1, 3, 7, 21 → exactly 4 divisors → sum = 32
// 4 has 3 divisors, 7 has 2 divisors → ignored
// Answer = 32

#include <vector>
using namespace std;

class Solution {
public:
    int sumFourDivisors(vector<int>& nums) {
        int totalSum = 0;

        for (int num : nums) {
            int count = 0;
            int sum = 0;

            for (int i = 1; i * i <= num; i++) {
                if (num % i == 0) {
                    int d1 = i;
                    int d2 = num / i;

                    if (d1 == d2) {
                        count += 1;
                        sum += d1;
                    } else {
                        count += 2;
                        sum += d1 + d2;
                    }

                    if (count > 4) {
                        break;
                    }
                }
            }

            if (count == 4) {
                totalSum += sum;
            }
        }

        return totalSum;
    }
};


// Explanation:
// For each number, we find its divisors by iterating up to its square root.
// Every divisor i gives a paired divisor num / i.
// We count and sum divisors carefully to avoid double counting perfect squares.
//
// If divisor count exceeds 4, we stop early.
// Only numbers with exactly 4 divisors contribute to the final sum.
//
// Time Complexity:
// O(n * sqrt(max(nums[i])))
//
// Space Complexity:
// O(1)