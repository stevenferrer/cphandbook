#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct Node {
  int key, dist;
};

// max_dist returns the farthest node from x
Node max_dist(const vector<vector<int>>& adj, int n, int x) {
  vector<bool> vis(n + 1, false);
  vector<int> dist(n + 1, 0);

  stack<int> s;
  s.push(x);
  dist[x] = 0;

  // find farthest node b from root
  int max_distance = 0, b;
  while (!s.empty()) {
    auto v = s.top();
    s.pop();

    if (vis[v]) {
      continue;
    }
    vis[v] = true;

    for (auto u : adj[v]) {
      if (vis[u]) {
        continue;
      }

      dist[u] += dist[v] + 1;
      if (dist[u] > max_distance) {
        max_distance = dist[u];
        b = u;
      }
      s.push(u);
    }
  }

  return Node{.key = b, .dist = max_distance};
}

int dfs_diameter(const vector<vector<int>>& adj, int n, int x) {
  auto b = max_dist(adj, n, x);
  auto c = max_dist(adj, n, b.key);
  return c.dist;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;

  vector<vector<int>> adj(n + 1);

  int a, b;
  while (cin >> a >> b) {
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  cout << dfs_diameter(adj, n, 1);
}
