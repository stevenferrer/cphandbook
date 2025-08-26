#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Cell {
  int r, c;
  bool operator==(const Cell& rhs) const { return (r == rhs.r && c == rhs.c); }
  bool operator!=(const Cell& rhs) const { return !(*this == rhs); }
};

// right, down, left, up
const int delta[] = {0, 1, 0, -1, 0};
const char direction[] = {'R', 'D', 'L', 'U'};

const int INF = 1e9;

bool is_exit_cell(vector<string>& grid, int n, int m, int r, int c) {
  return (grid[r][c] == '.' || grid[r][c] == 'A') &&
         (r == 0 || c == 0 || r == n - 1 || c == m - 1);
}

void bfs(vector<string>& grid, int n, int m, vector<Cell> cells,
         vector<vector<pair<int, int>>>& dist, vector<vector<Cell>>& parent,
         vector<vector<char>>& path, bool person = true) {

  vector<vector<bool>> vis(n, vector<bool>(m, false));

  queue<Cell> q;
  for (auto cell : cells) {
    q.push(cell);
    if (person) {
      dist[cell.r][cell.c].first = 0;
    } else {
      dist[cell.r][cell.c].second = 0;
    }
  }

  while (!q.empty()) {
    auto cell = q.front();
    q.pop();

    int r = cell.r, c = cell.c;

    if (vis[r][c]) {
      continue;
    }
    vis[r][c] = true;

    for (int k = 0; k < 4; ++k) {
      int nr = r + delta[k];
      int nc = c + delta[k + 1];

      // bounds check
      if (nr < 0 || nc < 0 || nr >= n || nc >= m) {
        continue;
      }

      // skip walls and visited cells
      if (grid[nr][nc] == '#' || vis[nr][nc]) {
        continue;
      }

      if (person) {
        if (dist[r][c].first + 1 < dist[nr][nc].first) {
          dist[nr][nc].first = dist[r][c].first + 1;
          parent[nr][nc] = {r, c};
          path[nr][nc] = direction[k];
        }
      } else {
        if (dist[r][c].second + 1 < dist[nr][nc].second) {
          dist[nr][nc].second = dist[r][c].second + 1;
        }
      }

      q.push({nr, nc});
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, m;
  cin >> n >> m;

  vector<string> grid(n);
  vector<Cell> exit_cells;
  vector<Cell> monster_cells;

  Cell start;
  for (int r = 0; r < n; ++r) {
    cin >> grid[r];
    for (int c = 0; c < m; ++c) {
      if (grid[r][c] == 'M') {
        monster_cells.push_back({r, c});
        continue;
      }

      if (grid[r][c] == 'A') {
        start = {r, c};
      }
    }
  }

  vector<vector<Cell>> parent(n, vector<Cell>(m));
  vector<vector<char>> path(n, vector<char>(m));
  vector<vector<pair<int, int>>> dist(n, vector<pair<int, int>>(m, {INF, INF}));

  bfs(grid, n, m, monster_cells, dist, parent, path, false);
  bfs(grid, n, m, {start}, dist, parent, path);

  Cell exit = {-1, -1};
  int min_dist = INF;
  for (int r = 0; r < n; ++r) {
    for (int c = 0; c < m; ++c) {
      if (!is_exit_cell(grid, n, m, r, c)) {
        continue;
      }

      if (dist[r][c].first < dist[r][c].second && dist[r][c].first < min_dist) {
        exit = {r, c};
        min_dist = dist[r][c].first;
      }
    }
  }

  if (exit == Cell{-1, -1}) {
    cout << "NO";
    return 0;
  }

  string ans;
  auto pos = exit;
  while (pos != start) {
    int r = pos.r, c = pos.c;
    ans.push_back(path[r][c]);
    pos = parent[r][c];
  }

  cout << "YES\n";
  cout << ans.length() << "\n";
  for (auto it = ans.rbegin(); it != ans.rend(); ++it) {
    cout << *it;
  }
}
