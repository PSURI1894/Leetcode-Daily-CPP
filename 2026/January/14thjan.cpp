// Question:
// You are given a 2D integer array squares where squares[i] = [xi, yi, li]
// represents a square with bottom-left corner (xi, yi) and side length li.
// All squares are axis-aligned.
//
// Find the minimum y-coordinate of a horizontal line such that
// the total area covered by squares above the line
// equals the total area covered by squares below the line.
//
// IMPORTANT (Separate Squares II):
// - Overlapping areas must be counted ONLY ONCE.
// - Answers within 1e-5 of the actual answer are accepted.

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    double separateSquares(vector<vector<int>>& squares) {

        // Each square contributes two y-events:
        // start at y, end at y + l, carrying its x-interval [x, x + l]
        struct Event {
            double y;
            int type; // +1 = add interval, -1 = remove interval
            double x1, x2;
        };

        vector<Event> events;
        for (auto& s : squares) {
            double x = s[0], y = s[1], l = s[2];
            events.push_back({y, 1, x, x + l});
            events.push_back({y + l, -1, x, x + l});
        }

        sort(events.begin(), events.end(),
             [](const Event& a, const Event& b) {
                 return a.y < b.y;
             });

        vector<pair<double, double>> active; // active x-intervals

        // Helper to compute union length of active x-intervals
        auto unionLength = [&](void) {
            if (active.empty()) return 0.0;
            sort(active.begin(), active.end());
            double len = 0.0;
            double curL = active[0].first;
            double curR = active[0].second;

            for (int i = 1; i < active.size(); i++) {
                if (active[i].first > curR) {
                    len += curR - curL;
                    curL = active[i].first;
                    curR = active[i].second;
                } else {
                    curR = max(curR, active[i].second);
                }
            }
            len += curR - curL;
            return len;
        };

        vector<array<double, 3>> slabs; // {y1, y2, area}
        double totalArea = 0.0;

        double prevY = events[0].y;
        int i = 0;

        while (i < events.size()) {
            double currY = events[i].y;
            double dy = currY - prevY;

            if (dy > 0) {
                double width = unionLength();
                double area = width * dy;
                slabs.push_back({prevY, currY, area});
                totalArea += area;
            }

            // Process all events at this y
            while (i < events.size() && events[i].y == currY) {
                if (events[i].type == 1) {
                    active.push_back({events[i].x1, events[i].x2});
                } else {
                    auto it = find(active.begin(), active.end(),
                                   make_pair(events[i].x1, events[i].x2));
                    if (it != active.end()) active.erase(it);
                }
                i++;
            }

            prevY = currY;
        }

        // Find y where area below == area above == totalArea / 2
        double target = totalArea / 2.0;
        double accumulated = 0.0;

        for (auto& slab : slabs) {
            double y1 = slab[0], y2 = slab[1], area = slab[2];
            if (accumulated + area >= target) {
                double width = area / (y2 - y1);
                return y1 + (target - accumulated) / width;
            }
            accumulated += area;
        }

        return slabs.back()[1];
    }
};


// Explanation:
//
// This is a sweep-line + union-area problem.
//
// Key difference from Separate Squares I:
// - Overlapping areas must be counted only once, so we must compute UNION area.
//
// Approach:
// 1. Sweep a horizontal line upward along the y-axis.
// 2. Each square creates two events:
//    - entering at y
//    - leaving at y + l
// 3. Between consecutive y-events, the active squares do not change.
//    Their x-intervals form a set whose UNION length determines covered width.
// 4. Area of each horizontal slab = union_width × slab_height.
//
// After computing total union area:
// - We find the y where cumulative area below equals totalArea / 2.
// - Since area grows linearly inside a slab, we interpolate precisely.
//
// Time Complexity:
// O(n log n)
//
// Space Complexity:
// O(n)