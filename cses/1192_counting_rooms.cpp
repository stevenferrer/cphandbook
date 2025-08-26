#include <iostream>
#include <stack>
#include <tuple>
#include <vector>

using namespace std;

// (0,1), (1,0), (0,-1), (-1, 0)
const int directions[] = {0, 1, 0, -1, 0};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, m;
  cin >> n >> m;

  vector<vector<bool>> wall(n, vector<bool>(m, true));
  vector<vector<bool>> done(n, vector<bool>(m, true));
  vector<pair<int, int>> floors;

  for (int r = 0; r < n; ++r) {
    for (int c = 0; c < m; ++c) {
      char ch;
      cin >> ch;
      if (ch == '.') {
        wall[r][c] = false;
        done[r][c] = false;
        floors.push_back({r, c});
      }
    }
  }

  int rooms = 0;
  for (size_t i = 0; i < floors.size(); ++i) {
    int srow, scol;
    tie(srow, scol) = floors[i];

    // skip explored floor
    if (done[srow][scol]) {
      continue;
    }

    // explore the room
    stack<pair<int, int>> s;
    s.push({srow, scol});

    while (!s.empty()) {
      int r, c;
      tie(r, c) = s.top();
      s.pop();

      if (done[r][c]) {
        continue;
      }
      done[r][c] = true;

      for (int k = 0; k < 4; ++k) {
        int nr = r + directions[k];
        int nc = c + directions[k + 1];

        // check bounds and wall
        if (nr < 0 || nc < 0 || nr >= n || nc >= m || wall[nr][nc]) {
          continue;
        }

        s.push({nr, nc});
      }
    }

    ++rooms;
  }

  cout << rooms;
}
