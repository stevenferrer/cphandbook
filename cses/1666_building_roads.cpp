#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, m;
  cin >> n >> m;

  vector<vector<int>> adjl(n + 1);

  // build adj list with bidirectional connection
  int a, b;
  for (int i = 0; i < m; ++i) {
    cin >> a >> b;
    adjl[a].push_back(b);
    adjl[b].push_back(a);
  }

  vector<int> roots;
  vector<bool> visited(n + 1);

  // start a DFS and collect all roots
  for (int v = 1; v <= n; ++v) {
    // skip visited nodes
    if (visited[v]) {
      continue;
    }

    // start a DFS
    stack<int> s;
    s.push(v);

    while (!s.empty()) {
      int a = s.top();
      s.pop();

      if (visited[a]) {
        continue;
      }
      visited[a] = true;

      for (int b : adjl[a]) {
        s.push(b);
      }
    }

    roots.push_back(v);
  }

  int comps = roots.size() - 1;
  cout << comps << endl;

  for (int k = 0; k < comps; ++k) {
    cout << roots[k] << " " << roots[k + 1] << "\n";
  }
}
