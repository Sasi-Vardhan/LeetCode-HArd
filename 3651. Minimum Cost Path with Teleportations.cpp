/*
===============================================================================
PROBLEM SUMMARY
-------------------------------------------------------------------------------
We are given an m x n grid.
- Start at (0,0)
- End at (m-1,n-1)
- Normal moves: right or down (cost = destination cell value)
- Teleport moves: from (x,y) to ANY cell (i,j) such that
      grid[i][j] <= grid[x][y]
  Teleport cost = 0
- We can use at most k teleports

Goal: Find the minimum total cost to reach the destination.

===============================================================================
WHY NAIVE SOLUTIONS FAIL
-------------------------------------------------------------------------------
1) DFS + DP + visited
   - Teleport availability depends on visited history
   - DP state (x,y,k) is NOT independent
   - Leads to incorrect answers

2) BFS / Dijkstra with teleport scanning entire grid
   - From every state, scanning all m*n cells for teleport
   - Time complexity becomes:
         O((m*n)^2 * k)
   - Causes TLE for m,n up to 80

3) Using visited[x][y]
   - Same cell can be reached with different teleport counts
   - visited[x][y] incorrectly prunes valid states
   - Breaks correctness

===============================================================================
CORRECT MODEL
-------------------------------------------------------------------------------
This is a SHORTEST PATH problem on a 3D state graph.

State = (x, y, t)
  x, y : position in grid
  t    : number of teleports used so far

We use DIJKSTRA (BFS with priority_queue) because:
- Normal moves have positive cost
- Teleports have zero cost

We DO NOT use visited[].
Instead, we use:
  dist[x][y][t] = minimum cost to reach (x,y) using t teleports

===============================================================================
TELEPORT OPTIMIZATION (KEY IDEA)
-------------------------------------------------------------------------------
Teleport rule:
  From (x,y) you can teleport to ALL cells with value <= grid[x][y]

Naively scanning the grid every time causes TLE.

Optimization:
1) Pre-sort all cells by their grid value.
2) For each teleport layer t, maintain a pointer ptr[t].
3) ptr[t] tracks how many sorted cells have already been considered
   as teleport destinations for that teleport count.

Important invariant:
- Each cell is processed at most ONCE per teleport layer.
- ptr[t] only increases and is bounded by total cell count.

This converts teleport edges into an implicit adjacency list
that is traversed lazily and efficiently.

===============================================================================
TIME & SPACE COMPLEXITY
-------------------------------------------------------------------------------
Let N = m * n

States:
  O(N * k)

Teleport processing:
  Each cell is considered once per teleport layer:
  O(N * k)

Priority queue:
  log(N * k)

Overall Time:
  O(N * k * log(N * k))

Space:
  O(N * k)

This passes all constraints.

===============================================================================
WHY THIS IS CORRECT
-------------------------------------------------------------------------------
- Dijkstra guarantees the first time we reach a state with minimal cost
- dist[][][] ensures no invalid pruning
- ptr[t] ensures no repeated teleport work
- Teleport rules are fully respected
- No state is missed, no state is overcounted

===============================================================================
*/

class Solution {
public:
    int minCost(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        const int INF = 1e9;

        // dist[x][y][t] = min cost to reach (x,y) using t teleports
        vector<vector<vector<int>>> dist(
            m, vector<vector<int>>(n, vector<int>(k + 1, INF))
        );

        // Store all cells as (value, x, y)
        vector<tuple<int,int,int>> cells;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cells.push_back({grid[i][j], i, j});
            }
        }

        // Sort cells by grid value (ascending)
        sort(cells.begin(), cells.end());

        // ptr[t] = how many cells already processed as teleport
        // destinations for teleport count t
        vector<int> ptr(k + 1, 0);

        // Min-heap: (cost, x, y, teleports_used)
        priority_queue<
            tuple<int,int,int,int>,
            vector<tuple<int,int,int,int>>,
            greater<>
        > pq;

        dist[0][0][0] = 0;
        pq.push({0, 0, 0, 0});

        while (!pq.empty()) {
            auto [cost, x, y, t] = pq.top();
            pq.pop();

            // Skip if we already found a better way
            if (cost > dist[x][y][t]) continue;

            // Destination reached
            if (x == m - 1 && y == n - 1)
                return cost;

            // Move right
            if (y + 1 < n) {
                int nc = cost + grid[x][y + 1];
                if (nc < dist[x][y + 1][t]) {
                    dist[x][y + 1][t] = nc;
                    pq.push({nc, x, y + 1, t});
                }
            }

            // Move down
            if (x + 1 < m) {
                int nc = cost + grid[x + 1][y];
                if (nc < dist[x + 1][y][t]) {
                    dist[x + 1][y][t] = nc;
                    pq.push({nc, x + 1, y, t});
                }
            }

            // Teleport (optimized)
            if (t < k) {
                while (ptr[t] < cells.size() &&
                       get<0>(cells[ptr[t]]) <= grid[x][y]) {

                    auto [_, i, j] = cells[ptr[t]++];
                    if (cost < dist[i][j][t + 1]) {
                        dist[i][j][t + 1] = cost;
                        pq.push({cost, i, j, t + 1});
                    }
                }
            }
        }

        return -1; // Should not happen if destination is reachable
    }
};
