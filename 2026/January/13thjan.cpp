// Question:
// You are given a 2D integer array squares where squares[i] = [xi, yi, li]
// represents a square with bottom-left corner (xi, yi) and side length li.
// All squares are axis-aligned.
//
// Find the minimum y-coordinate of a horizontal line such that
// the total area of the squares strictly above the line
// equals the total area of the squares strictly below the line.
//
// Squares may overlap, and overlapping areas should be counted multiple times.
// Answers within 1e-5 of the correct value are accepted.

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    double separateSquares(vector<vector<int>>& squares) {

        // Function to compute (area_above - area_below) for a given y
        auto balance = [&](double y) {
            double diff = 0.0;

            for (auto& sq : squares) {
                double bottom = sq[1];
                double top = sq[1] + sq[2];
                double area = 1.0 * sq[2] * sq[2];

                if (y <= bottom) {
                    // Entire square is above the line
                    diff += area;
                } 
                else if (y >= top) {
                    // Entire square is below the line
                    diff -= area;
                } 
                else {
                    // Line cuts the square
                    double above = (top - y) * sq[2];
                    double below = (y - bottom) * sq[2];
                    diff += above - below;
                }
            }

            return diff;
        };

        // Binary search range
        double low = squares[0][1];
        double high = squares[0][1] + squares[0][2];

        for (auto& sq : squares) {
            low = min(low, (double)sq[1]);
            high = max(high, (double)(sq[1] + sq[2]));
        }

        // Binary search for y where balance(y) == 0
        for (int i = 0; i < 60; i++) {  // sufficient for 1e-5 precision
            double mid = (low + high) / 2.0;
            if (balance(mid) > 0) {
                low = mid;
            } else {
                high = mid;
            }
        }

        return low;
    }
};


// Explanation:
// We want a horizontal line y = c such that:
//   (total area above the line) == (total area below the line)
//
// Define a function f(c) = area_above - area_below.
// Our goal is to find c such that f(c) = 0.
//
// For each square:
// - If the line is completely below it → entire area contributes above
// - If the line is completely above it → entire area contributes below
// - If the line cuts through it → area is split proportionally
//
// The function f(c) is continuous and monotonically decreasing,
// so we can apply binary search on y.
//
// We binary search between the minimum bottom and maximum top of all squares,
// running enough iterations to guarantee the required precision.
//
// Time Complexity:
// O(n * log(precision))
//
// Space Complexity:
// O(1)