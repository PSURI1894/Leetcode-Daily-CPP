// Question:
// Given an m x n matrix mat and an integer threshold,
// return the maximum side length of a square such that the sum of all elements
// inside the square is less than or equal to threshold.
// If no such square exists, return 0.

class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        int m = mat.size();
        int n = mat[0].size();

        // Prefix sum matrix
        // ps[i][j] = sum of submatrix from (0,0) to (i-1,j-1)
        vector<vector<int>> ps(m + 1, vector<int>(n + 1, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                ps[i + 1][j + 1] =
                    mat[i][j]
                    + ps[i][j + 1]
                    + ps[i + 1][j]
                    - ps[i][j];
            }
        }

        int left = 0, right = min(m, n);
        int ans = 0;

        // Binary search on side length
        while (left <= right) {
            int mid = (left + right) / 2;
            bool found = false;

            for (int i = 0; i + mid <= m && !found; i++) {
                for (int j = 0; j + mid <= n; j++) {
                    int sum =
                        ps[i + mid][j + mid]
                        - ps[i][j + mid]
                        - ps[i + mid][j]
                        + ps[i][j];

                    if (sum <= threshold) {
                        found = true;
                        break;
                    }
                }
            }

            if (found) {
                ans = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return ans;
    }
};

/*
Explanation:
- Build a 2D prefix sum array to compute any square sum in O(1).
- The condition "sum ≤ threshold" is monotonic with respect to square size.
- Binary search is used on the side length.
- For each candidate size k, all k x k squares are checked.
- The largest valid k is returned.

Time Complexity: O(m * n * log(min(m, n)))
Space Complexity: O(m * n)
*/
