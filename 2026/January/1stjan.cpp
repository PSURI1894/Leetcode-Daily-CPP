// Question:
// You are given a large integer represented as an integer array digits,
// where each digits[i] is the ith digit of the integer.
// The digits are ordered from most significant to least significant.
// The integer does not contain any leading zeros.
//
// Increment the large integer by one and return the resulting array of digits.

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();

        // Start from the last digit and move left
        for (int i = n - 1; i >= 0; i--) {
            if (digits[i] < 9) {
                digits[i]++;
                return digits;
            }
            digits[i] = 0;
        }

        // If all digits were 9, we need an extra digit at the front
        vector<int> result(n + 1, 0);
        result[0] = 1;
        return result;
    }
};

// Explanation:
// This follows the same logic as manual addition.
// We traverse the array from right to left and try to add 1.
// If a digit is less than 9, we increment it and stop.
// If a digit is 9, it becomes 0 and the carry moves left.
// If all digits are 9, we create a new vector with one extra space
// and set the first digit to 1.
// Time Complexity: O(n)
// Space Complexity: O(1) extra space (excluding output vector)
