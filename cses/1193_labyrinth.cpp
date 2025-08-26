#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

// row, col
using Cell = pair<int, int>;

const int delta[] = {0, 1, 0, -1, 0};
const int letter[] = {'R', 'D', 'L', 'U'};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, m;
  cin >> n >> m;

  vector<string> grid(n);
  Cell start, end;

  for (int r = 0; r < n; ++r) {
    cin >> grid[r];
    for (int c = 0; c < m; ++c) {
      if (grid[r][c] == 'A') {
        start = {r, c};
      }
      if (grid[r][c] == 'B') {
        end = {r, c};
      }
    }
  }

  vector<vector<bool>> done(n, vector<bool>(m, false));
  vector<vector<Cell>> parent(n, vector<Cell>(m));
  vector<vector<char>> lastletter(n, vector<char>(m));

  queue<Cell> q;
  q.push(start);

  while (!q.empty()) {
    int r, c;
    tie(r, c) = q.front();
    q.pop();

    for (int k = 0; k < 4; ++k) {
      int nr = r + delta[k];
      int nc = c + delta[k + 1];

      // bounds check
      if (nr < 0 || nc < 0 || nr >= n || nc >= m) {
        continue;
      }

      // wall
      if (grid[nr][nc] == '#' || done[nr][nc]) {
        continue;
      }

      done[nr][nc] = true;
      parent[nr][nc] = {r, c};
      lastletter[nr][nc] = letter[k];
      q.emplace(nr, nc);
    }
  }

  if (!done[end.first][end.second]) {
    cout << "NO";
    return 0;
  }

  string ans;
  auto pos = end;
  while (pos != start) {
    int r, c;
    tie(r, c) = pos;
    ans += lastletter[r][c];
    pos = parent[r][c];
  }
  reverse(ans.begin(), ans.end());

  cout << "YES\n";
  cout << ans.size() << "\n";
  cout << ans;
}
