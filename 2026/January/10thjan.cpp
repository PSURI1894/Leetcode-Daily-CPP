// Question:
// Given two strings s1 and s2, return the minimum ASCII sum of deleted characters
// required to make the two strings equal.
//
// You may delete characters from either string.
// The cost of deleting a character is its ASCII value.
// The goal is to minimize the total deletion cost.

#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        int n = s1.size();
        int m = s2.size();

        // dp[i][j] = minimum ASCII delete sum to make s1[i:] and s2[j:] equal
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // Base case: delete all remaining characters from s1
        for (int i = n - 1; i >= 0; i--) {
            dp[i][m] = dp[i + 1][m] + s1[i];
        }

        // Base case: delete all remaining characters from s2
        for (int j = m - 1; j >= 0; j--) {
            dp[n][j] = dp[n][j + 1] + s2[j];
        }

        // Fill the DP table
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                if (s1[i] == s2[j]) {
                    dp[i][j] = dp[i + 1][j + 1];
                } else {
                    dp[i][j] = min(
                        s1[i] + dp[i + 1][j],
                        s2[j] + dp[i][j + 1]
                    );
                }
            }
        }

        return dp[0][0];
    }
};


// Explanation:
// This is a Dynamic Programming approach inspired by Longest Common Subsequence.
//
// dp[i][j] stores the minimum ASCII delete sum to make substrings
// s1[i:] and s2[j:] equal.
//
// If characters match, no deletion is needed.
// If they do not match, we delete one character (from s1 or s2)
// and add its ASCII value to the cost.
//
// Base cases handle when one string is exhausted.
//
// The final result dp[0][0] gives the minimum cost.
//
// Time Complexity: O(n * m)
// Space Complexity: O(n * m)