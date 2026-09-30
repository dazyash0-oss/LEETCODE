class Solution {
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();

        if (m == 1 && n == 1) return 0;

        // enough eliminations to walk straight through anything
        if (k >= m + n - 2) return m + n - 2;

        // best[r][c] = max remaining eliminations seen when reaching (r, c)
        vector<vector<int>> best(m, vector<int>(n, -1));


        queue<vector<int>> q; // each entry is {r, c, used}
        q.push({0, 0, k});
        best[0][0] = k;

        int dr[4] = {0, 0, 1, -1};
        int dc[4] = {1, -1, 0, 0};
        int steps = 0;

        while (!q.empty()) {
            steps++;
            int size = q.size();
            for (int i = 0; i < size; i++) {
                vector<int> cur = q.front();
                q.pop();
                int r = cur[0], c = cur[1], used = cur[2];

                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr < 0 || nc < 0 || nr >= m || nc >= n) continue;

                    // stepping onto a wall uses the one elimination
                    int nrem = used - grid[nr][nc]; 
                    // run out of eliminations
                    if (nrem < 0) continue;
                    // already been here in this state
                    if (best[nr][nc] >= nrem) continue;
                    best[nr][nc] = nrem;

                    if (nr == m - 1 && nc == n - 1) return steps;

                    q.push({nr, nc, nrem});
                }
            }
        }
        return -1;
    }
};