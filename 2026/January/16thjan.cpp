// Question:
// You are given two integers n and m and two integer arrays hBars and vBars.
// The grid has (n + 2) horizontal bars and (m + 2) vertical bars, creating 1x1 unit cells.
//
// You can remove some bars from hBars (horizontal) and vBars (vertical).
// Other bars are fixed and cannot be removed.
//
// After removing bars, holes (empty regions) are formed.
// Return the maximum possible area of a square-shaped hole in the grid.

class Solution {
public:
    int maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences) {
        const long long MOD = 1e9 + 7;

        // Add boundary fences
        hFences.push_back(1);
        hFences.push_back(m);
        vFences.push_back(1);
        vFences.push_back(n);

        sort(hFences.begin(), hFences.end());
        sort(vFences.begin(), vFences.end());

        // Store all possible heights
        unordered_set<int> heights;
        for (int i = 0; i < hFences.size(); i++) {
            for (int j = i + 1; j < hFences.size(); j++) {
                heights.insert(hFences[j] - hFences[i]);
            }
        }

        // Find largest square side
        int maxSide = 0;
        for (int i = 0; i < vFences.size(); i++) {
            for (int j = i + 1; j < vFences.size(); j++) {
                int width = vFences[j] - vFences[i];
                if (heights.count(width)) {
                    maxSide = max(maxSide, width);
                }
            }
        }

        if (maxSide == 0) return -1;
        return (maxSide * 1LL * maxSide) % MOD;
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
