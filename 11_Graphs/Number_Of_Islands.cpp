#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution1 {
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
public:
    int numIslands(vector<vector<char>>& grid) {
        int ROWS = grid.size(), COLS = grid[0].size();
        int islands = 0;

        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                if (grid[r][c] == '1') {
                    dfs(grid, r, c);
                    islands++;
                }
            }
        }

        return islands;
    }

    void dfs(vector<vector<char>>& grid, int r, int c) {
        if (r < 0 || c < 0 || r >= grid.size() ||
            c >= grid[0].size() || grid[r][c] == '0') {
            return;
        }

        grid[r][c] = '0';
        for (int i = 0; i < 4; i++) {
            dfs(grid, r + directions[i][0], c + directions[i][1]);
        }
    }
};

class Solution2 {
    int directions[4][2] = {{1, 0}, {-1, 0},
                            {0, 1}, {0, -1}};
public:
    int numIslands(vector<vector<char>>& grid) {
        int ROWS = grid.size(), COLS = grid[0].size();
        int islands = 0;

        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                if (grid[r][c] == '1') {
                    bfs(grid, r, c);
                    islands++;
                }
            }
        }

        return islands;
    }

    void bfs(vector<vector<char>>& grid, int r, int c) {
        queue<pair<int, int>> q;
        grid[r][c] = '0';
        q.push({r, c});

        while (!q.empty()) {
            auto node = q.front();q.pop();
            int row = node.first, col = node.second;
            for (int i = 0; i < 4; i++) {
                int nr = row + directions[i][0];
                int nc = col + directions[i][1];
                if (nr >= 0 && nc >= 0 && nr < grid.size() &&
                    nc < grid[0].size() && grid[nr][nc] == '1') {
                    q.push({nr, nc});
                    grid[nr][nc] = '0';
                }
            }
        }
    }
};

class DSU {
    vector<int> Parent, Size;
public:
    DSU(int n) {
        Parent.resize(n + 1);
        Size.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            Parent[i] = i;
            Size[i] = 1;
        }
    }

    int find(int node) {
        if (node != Parent[node]) {
            Parent[node] = find(Parent[node]);
        }
        return Parent[node];
    }

    bool unionBySize(int u, int v) {
        int pu = find(u);
        int pv = find(v);
        if (pu == pv) return false;
        if (Size[pu] >= Size[pv]) {
            Size[pu] += Size[pv];
            Parent[pv] = pu;
        } else {
            Size[pv] += Size[pu];
            Parent[pu] = pv;
        }
        return true;
    }
};

class Solution3 {
public:
    int numIslands(vector<vector<char>>& grid) {
        int ROWS = grid.size();
        int COLS = grid[0].size();
        DSU dsu(ROWS * COLS);

        int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int islands = 0;

        auto index = [&](int r, int c) {
            return r * COLS + c;
        };

        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                if (grid[r][c] == '1') {
                    islands++;
                    for (auto& d : directions) {
                        int nr = r + d[0];
                        int nc = c + d[1];
                        if (nr >= 0 && nc >= 0 && nr < ROWS &&
                            nc < COLS && grid[nr][nc] == '1') {
                            if (dsu.unionBySize(index(r, c), index(nr, nc))) {
                                islands--;
                            }
                        }
                    }
                }
            }
        }

        return islands;
    }
};

int main(){
    vector<vector<char>> grid = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };

    vector<vector<char>> g1 = grid;
    vector<vector<char>> g2 = grid;
    vector<vector<char>> g3 = grid;

    Solution1 s1;
    Solution2 s2;
    Solution3 s3;

    cout << "DFS Solution: " << s1.numIslands(g1) << endl;
    cout << "BFS Solution: " << s2.numIslands(g2) << endl;
    cout << "DSU Solution: " << s3.numIslands(g3) << endl;
    return 0;
}