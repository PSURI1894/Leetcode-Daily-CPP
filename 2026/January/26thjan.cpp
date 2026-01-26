/*
Question:
1200. Minimum Absolute Difference

Given an array of distinct integers arr, find all pairs of elements
with the minimum absolute difference between any two elements.

Return the list of pairs in ascending order.
Each pair [a, b] must satisfy:
- a < b
- b - a equals the minimum absolute difference.
*/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
        vector<vector<int>> result;
        
        // Step 1: Sort the array
        sort(arr.begin(), arr.end());
        
        // Step 2: Find the minimum absolute difference
        int minDiff = INT_MAX;
        for (int i = 1; i < arr.size(); i++) {
            minDiff = min(minDiff, arr[i] - arr[i - 1]);
        }
        
        // Step 3: Collect all pairs with this minimum difference
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] - arr[i - 1] == minDiff) {
                result.push_back({arr[i - 1], arr[i]});
            }
        }
        
        return result;
    }
};