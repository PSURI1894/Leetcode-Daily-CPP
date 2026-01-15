// Question:
// You are given two integers n and m and two integer arrays hBars and vBars.
// The grid has (n + 2) horizontal bars and (m + 2) vertical bars, creating 1x1 unit cells.
//
// You can remove some bars from hBars (horizontal) and vBars (vertical).
// Other bars are fixed and cannot be removed.
//
// After removing bars, holes (empty regions) are formed.
// Return the maximum possible area of a square-shaped hole in the grid.

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maximizeSquareHoleArea(int n, int m, vector<int>& hBars, vector<int>& vBars) {

        // Sort removable bars
        sort(hBars.begin(), hBars.end());
        sort(vBars.begin(), vBars.end());

        // Find longest consecutive sequence in hBars
        int maxH = 1, curr = 1;
        for (int i = 1; i < hBars.size(); i++) {
            if (hBars[i] == hBars[i - 1] + 1) {
                curr++;
            } else {
                curr = 1;
            }
            maxH = max(maxH, curr);
        }

        // Find longest consecutive sequence in vBars
        int maxV = 1;
        curr = 1;
        for (int i = 1; i < vBars.size(); i++) {
            if (vBars[i] == vBars[i - 1] + 1) {
                curr++;
            } else {
                curr = 1;
            }
            maxV = max(maxV, curr);
        }

        // Largest square side length
        int side = min(maxH + 1, maxV + 1);

        return side * side;
    }
};


// Explanation:
// Removing k consecutive horizontal bars merges (k + 1) rows.
// Removing k consecutive vertical bars merges (k + 1) columns.
//
// To form a square hole:
// - Height = longest consecutive removed horizontal bars + 1
// - Width  = longest consecutive removed vertical bars + 1
//
// The maximum square side is the minimum of height and width.
// The area is side × side.
//
// Time Complexity: O(h log h + v log v)
// Space Complexity: O(1)