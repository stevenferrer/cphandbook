#include <iostream>
#include <vector>

using namespace std;

int subordinate(const vector<vector<int>>& adj, vector<int>& sub, int x) {
  if (adj[x].size() == 0) {
    return 0;
  }

  for (auto u : adj[x]) {
    sub[u] = subordinate(adj, sub, u);
    sub[x] += sub[u] + 1;
  }

  return sub[x];
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;

  vector<vector<int>> adj(n + 1);

  int u;
  for (int v = 2; v <= n; ++v) {
    cin >> u;
    adj[u].push_back(v);
  }

  vector<int> sub(n + 1, 0);
  subordinate(adj, sub, 1);

  for (int x = 1; x <= n; ++x) {
    cout << sub[x] << " ";
  }
}
