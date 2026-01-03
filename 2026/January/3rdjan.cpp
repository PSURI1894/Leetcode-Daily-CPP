// Question:
// You have a grid of size n x 3 and you want to paint each cell of the grid
// with exactly one of the three colors: Red, Yellow, or Green.
// You must ensure that no two adjacent cells (horizontal or vertical)
// have the same color.
//
// Given n, return the number of ways to paint the grid.
// Since the answer can be very large, return it modulo 1e9 + 7.


class Solution {
public:
    int numOfWays(int n) {
        const long MOD = 1000000007;

        // aba: patterns like RYG (first and third same)
        // abc: patterns like RGB (all different)
        long aba = 6; // 3 * 2
        long abc = 6; // 3 * 2 * 1

        for (int i = 2; i <= n; i++) {
            long newAba = (aba * 3 + abc * 2) % MOD;
            long newAbc = (aba * 2 + abc * 2) % MOD;

            aba = newAba;
            abc = newAbc;
        }

        return (aba + abc) % MOD;
    }
};


// Explanation:
// For each row of 3 cells, there are only two valid pattern types:
//
// 1) aba pattern: first and third cells have the same color (e.g., R G R)
// 2) abc pattern: all three cells have different colors (e.g., R G B)
//
// For the first row:
// aba = 6 ways
// abc = 6 ways
//
// For every next row:
// - aba can be formed from:
//     previous aba in 3 ways
//     previous abc in 2 ways
// - abc can be formed from:
//     previous aba in 2 ways
//     previous abc in 2 ways
//
// We use dynamic programming with constant space by only tracking
// counts of aba and abc for the previous row.
//
// Time Complexity: O(n)
// Space Complexity: O(1)
