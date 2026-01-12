// Question:
// On a 2D plane, there are n points with integer coordinates points[i] = [xi, yi].
// You need to visit all the points in the given order.
//
// In 1 second, you can:
// - Move vertically by 1 unit, or
// - Move horizontally by 1 unit, or
// - Move diagonally by 1 unit (i.e., move 1 unit vertically and 1 unit horizontally).
//
// Return the minimum time in seconds to visit all the points in order.

#include <vector>
#include <cmath>
using namespace std;

class Solution {
public:
    int minTimeToVisitAllPoints(vector<vector<int>>& points) {
        int totalTime = 0;

        for (int i = 1; i < points.size(); i++) {
            int x1 = points[i - 1][0];
            int y1 = points[i - 1][1];
            int x2 = points[i][0];
            int y2 = points[i][1];

            int dx = abs(x2 - x1);
            int dy = abs(y2 - y1);

            // Minimum time between two points
            totalTime += max(dx, dy);
        }

        return totalTime;
    }
};


// Explanation:
// A diagonal move reduces both horizontal and vertical distance by 1 in one second.
// So we should always use diagonal moves as much as possible.
//
// For moving from (x1, y1) to (x2, y2):
// - Horizontal distance = |x2 - x1|
// - Vertical distance   = |y2 - y1|
//
// Each diagonal step reduces both by 1, until one direction is exhausted.
// The remaining distance is covered by straight moves.
//
// Therefore, the minimum time required is:
// max(|x2 - x1|, |y2 - y1|)
//
// We compute this for every consecutive pair of points and sum it.
//
// Time Complexity: O(n)
// Space Complexity: O(1)