#include <iostream>
#include <stack>
#include <vector>

using namespace std;

void printCycle(vector<int>& pred, int start, int end) {
  vector<int> path;

  path.push_back(end);
  int v = start;
  while (v != end) {
    path.push_back(v);
    v = pred[v];
  }
  path.push_back(end);

  cout << path.size() << "\n";
  for (auto v : path) {
    cout << v << " ";
  }
}

bool dfs(vector<vector<int>>& adjl, vector<bool>& done, vector<int>& pred,
         int start) {

  stack<int> s;
  s.push(start);

  while (!s.empty()) {
    auto a = s.top();
    s.pop();

    if (done[a]) {
      continue;
    }
    done[a] = true;

    // emulate recursive order by using reverse iterator
    for (auto it = adjl[a].rbegin(); it != adjl[a].rend(); ++it) {
      int b = *it;
      // skip predecessor node
      if (pred[a] == b) {
        continue;
      }

      // check for cycle
      if (done[b]) {
        printCycle(pred, a, b);
        return true;
      }

      pred[b] = a;
      s.push(b);
    }
  }

  return false;
}

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

  vector<bool> done(n + 1, false);
  vector<int> pred(n + 1, -1);
  for (int v = 1; v <= n; ++v) {
    if (dfs(adjl, done, pred, v)) {
      return 0;
    }
  }

  cout << "IMPOSSIBLE" << endl;
}
