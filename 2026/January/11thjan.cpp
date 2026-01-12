// Question:
// Given a rows x cols binary matrix filled with '0's and '1's,
// find the largest rectangle containing only '1's and return its area.
//
// Each rectangle must be made up entirely of contiguous '1's.

#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;

        int cols = matrix[0].size();
        vector<int> heights(cols, 0);
        int maxArea = 0;

        for (auto& row : matrix) {
            // Build histogram heights for this row
            for (int i = 0; i < cols; i++) {
                if (row[i] == '1') {
                    heights[i]++;
                } else {
                    heights[i] = 0;
                }
            }

            // Largest Rectangle in Histogram
            stack<int> st;
            for (int i = 0; i <= cols; i++) {
                int currHeight = (i == cols) ? 0 : heights[i];

                while (!st.empty() && currHeight < heights[st.top()]) {
                    int height = heights[st.top()];
                    st.pop();
                    int width = st.empty() ? i : i - st.top() - 1;
                    maxArea = max(maxArea, height * width);
                }

                st.push(i);
            }
        }

        return maxArea;
    }
};


// Explanation:
// We reduce the 2D matrix problem to multiple "Largest Rectangle in Histogram" problems.
//
// Approach:
// - For each row, treat it as the base of a histogram.
// - heights[j] counts consecutive '1's above the current row in column j.
// - Use a monotonic increasing stack to compute the largest rectangle area.
//
// Stack logic:
// - Store indices of increasing heights.
// - When a lower height is encountered, pop from stack and calculate area.
// - Width is determined by current index and new top of stack.
//
// A sentinel zero height is added at the end to clear the stack.
//
// Time Complexity: O(rows * cols)
// Space Complexity: O(cols)
