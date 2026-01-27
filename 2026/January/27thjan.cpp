// Question:
// 3650. Minimum Cost Path with Edge Reversals
//
// You are given a directed, weighted graph with n nodes (0 to n-1).
// edges[i] = [u, v, w] represents a directed edge u -> v with cost w.
//
// Each node has a switch usable at most once:
// - When you arrive at node u, you may reverse ONE incoming edge (x -> u)
//   into (u -> x) and immediately traverse it.
// - Traversing a reversed edge costs 2 * w.
// - The reversal is valid only for that single move.
//
// Return the minimum total cost to travel from node 0 to node n-1.
// If it is not possible, return -1.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minCost(int n, vector<vector<int>>& edges) {

        // Build adjacency list
        // For every edge u -> v with cost w:
        // 1) Normal traversal: u -> v (cost w)
        // 2) Reverse option:    v -> u (cost 2*w)
        //
        // This works because each node’s switch is local and can be used once,
        // and an optimal shortest path never benefits from using the same node’s
        // switch more than once.
        vector<vector<pair<int, int>>> graph(n);

        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            graph[u].push_back({v, w});
            graph[v].push_back({u, 2 * w});
        }

        // Dijkstra’s algorithm
        vector<long long> dist(n, LLONG_MAX);
        priority_queue<pair<long long, int>,
                       vector<pair<long long, int>>,
                       greater<pair<long long, int>>> pq;

        dist[0] = 0;
        pq.push({0, 0});

        while (!pq.empty()) {
            auto [cost, u] = pq.top();
            pq.pop();

            if (cost > dist[u]) continue;

            for (auto &[v, w] : graph[u]) {
                long long newCost = cost + w;
                if (newCost < dist[v]) {
                    dist[v] = newCost;
                    pq.push({newCost, v});
                }
            }
        }

        return dist[n - 1] == LLONG_MAX ? -1 : (int)dist[n - 1];
    }
};

/*
Explanation:

Key Insight:
- Each node has its own independent switch.
- Using a switch just allows one reversed traversal of an incoming edge.
- In a shortest-path setting, revisiting a node at a higher cost is never optimal,
  so a node’s switch will never be beneficially used more than once.
- Therefore, we do NOT need extra state to track switch usage.

Graph Transformation:
For every original edge:
    u -> v (cost w)
We add:
    u -> v (cost w)      // normal move
    v -> u (cost 2*w)    // reverse using v's switch

After this transformation, the problem becomes a standard shortest-path problem.

Algorithm:
- Build the transformed graph.
- Run Dijkstra from node 0.
- The shortest distance to node n-1 is the answer.

Correctness:
- Multiple reversals at different nodes are allowed.
- Each reversed edge is used at most once in any optimal path.
- All edge costs are positive, so Dijkstra is valid.

Time Complexity:
O((n + m) log n), where m = number of edges

Space Complexity:
O(n + m)

This is the editorial-intended solution.
*/
