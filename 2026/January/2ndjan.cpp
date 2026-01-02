// Question:
// You are given an integer array nums with the following properties:
// 1) nums.length = 2 * n
// 2) nums contains n + 1 unique elements
// 3) Exactly one element in nums is repeated n times
//
// Return the element that is repeated n times.

#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int repeatedNTimes(vector<int>& nums) {
        unordered_set<int> seen;

        for (int num : nums) {
            if (seen.count(num)) {
                return num;
            }
            seen.insert(num);
        }

        return -1; // Will never be reached due to problem constraints
    }
};

// Explanation:
// Only one element appears multiple times, while all others appear once.
// We iterate through the array and store seen elements in an unordered_set.
// If an element is encountered again, it must be the one repeated n times.
// We return it immediately.
//
// Time Complexity: O(n)
// Space Complexity: O(n)
