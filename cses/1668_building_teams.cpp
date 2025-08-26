#include <iostream>
#include <stack>
#include <tuple>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, m;
  cin >> n >> m;

  vector<vector<int>> adjl(n + 1);

  int a, b;
  for (int i = 0; i < m; ++i) {
    cin >> a >> b;
    adjl[a].push_back(b);
    adjl[b].push_back(a);
  }

  vector<bool> visited(n + 1);
  vector<int> teams(n + 1, -1);

  for (int v = 1; v <= n; ++v) {
    if (visited[v]) {
      continue;
    }

    stack<pair<int, int>> s;
    s.push({v, 0});

    while (!s.empty()) {
      int a, t;
      tie(a, t) = s.top();
      s.pop();

      if (visited[a]) {
        continue;
      }
      visited[a] = true;
      teams[a] = t;

      for (auto b : adjl[a]) {
        if (teams[b] == teams[a]) {
          // a and b are in the same team!
          cout << "IMPOSSIBLE";
          return 0;
        }

        s.push({b, !t});
      }
    }
  }

  // print teams
  for (int v = 1; v <= n; ++v) {
    cout << teams[v] + 1 << " ";
  }
}
