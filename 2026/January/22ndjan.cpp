// Question:
// Given two binary strings a and b, return their sum as a binary string.
//
// Each string consists only of characters '0' or '1'.
// The binary sum should be returned without leading zeros (unless the result is "0").

class Solution {
public:
    string addBinary(string a, string b) {
        int i = a.size() - 1;
        int j = b.size() - 1;
        int carry = 0;
        string result = "";

        // Process both strings from right to left
        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;

            if (i >= 0) {
                sum += (a[i] - '0');
                i--;
            }
            if (j >= 0) {
                sum += (b[j] - '0');
                j--;
            }

            // Current bit is sum % 2
            result.push_back((sum % 2) + '0');

            // Carry for next iteration
            carry = sum / 2;
        }

        // The result is built in reverse order
        reverse(result.begin(), result.end());
        return result;
    }
};

/*
Explanation:
- We add the binary numbers exactly like manual addition.
- Start from the last characters of both strings.
- Add corresponding bits along with carry.
- The current bit is (sum % 2) and carry is (sum / 2).
- Continue until both strings are fully processed and no carry remains.
- Since we build the result from least significant bit to most significant bit,
  we reverse the string at the end.

Time Complexity:
O(max(len(a), len(b)))

Space Complexity:
O(max(len(a), len(b)))
*/