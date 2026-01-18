// Question:
// A k x k magic square is a k x k grid filled with integers such that:
// - Every row sum is equal
// - Every column sum is equal
// - Both diagonal sums are equal
//
// A 1 x 1 grid is always a magic square.
//
// Given an m x n integer grid, return the size (side length k)
// of the largest magic square that can be found in the grid.

class Solution {
public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // Prefix sums for rows and columns
        vector<vector<int>> rowPS(m, vector<int>(n + 1, 0));
        vector<vector<int>> colPS(m + 1, vector<int>(n, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                rowPS[i][j + 1] = rowPS[i][j] + grid[i][j];
                colPS[i + 1][j] = colPS[i][j] + grid[i][j];
            }
        }

        // Try square sizes from largest to smallest
        for (int k = min(m, n); k > 1; k--) {
            for (int i = 0; i + k <= m; i++) {
                for (int j = 0; j + k <= n; j++) {

                    int target = rowPS[i][j + k] - rowPS[i][j];
                    bool valid = true;

                    // Check all rows
                    for (int r = i; r < i + k; r++) {
                        if (rowPS[r][j + k] - rowPS[r][j] != target) {
                            valid = false;
                            break;
                        }
                    }
                    if (!valid) continue;

                    // Check all columns
                    for (int c = j; c < j + k; c++) {
                        if (colPS[i + k][c] - colPS[i][c] != target) {
                            valid = false;
                            break;
                        }
                    }
                    if (!valid) continue;

                    // Check both diagonals
                    int diag1 = 0, diag2 = 0;
                    for (int d = 0; d < k; d++) {
                        diag1 += grid[i + d][j + d];
                        diag2 += grid[i + d][j + k - 1 - d];
                    }

                    if (diag1 == target && diag2 == target) {
                        return k;
                    }
                }
            }
        }

        return 1; // Every single cell is a valid 1x1 magic square
    }
};

/*
Explanation:
- Any 1x1 cell is trivially a magic square.
- We use prefix sums to compute row and column sums in O(1).
- We attempt all possible square sizes starting from the largest.
- For each k x k subgrid:
    - All row sums must match.
    - All column sums must match.
    - Both diagonal sums must match the same value.
- The first valid square found is the largest, so we return immediately.

Time Complexity: O(min(m, n)^3)
Space Complexity: O(m * n)
*/