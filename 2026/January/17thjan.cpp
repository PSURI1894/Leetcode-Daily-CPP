// Question:
// You are given multiple axis-aligned rectangles on a 2D plane.
// Each rectangle is defined by its bottom-left and top-right coordinates.
//
// You must find the maximum possible area of a square that can be placed
// completely inside the intersection region of at least two rectangles.
//
// If no two rectangles intersect, return 0.

class Solution {
public:
    long long largestSquareArea(vector<vector<int>>& bottomLeft,
                                vector<vector<int>>& topRight) {
        int n = bottomLeft.size();
        long long maxArea = 0;

        // Check intersection for every pair of rectangles
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {

                int left   = max(bottomLeft[i][0], bottomLeft[j][0]);
                int bottom = max(bottomLeft[i][1], bottomLeft[j][1]);
                int right  = min(topRight[i][0], topRight[j][0]);
                int top    = min(topRight[i][1], topRight[j][1]);

                // If intersection exists
                if (right > left && top > bottom) {
                    long long side = min(right - left, top - bottom);
                    maxArea = max(maxArea, side * side);
                }
            }
        }
        return maxArea;
    }
};

/*
Explanation:
- Any square must lie completely inside an overlapping region.
- For each rectangle pair, compute the intersection box.
- The largest square inside it has side = min(width, height).
- Compare areas across all pairs.
- If no intersection exists, return 0.

Time Complexity: O(n^2)
Space Complexity: O(1)
*/
