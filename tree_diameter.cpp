#include <algorithm>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

pair<int, int> max_dist(const vector<vector<int>>& adj, int n, int x) {
  vector<bool> vis(n + 1, false);
  vector<int> dist(n + 1, 0);

  stack<int> s;
  s.push(x);
  dist[x] = 0;

  // find farthest node b from root
  int maxd = 0, b;
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
      if (dist[u] > maxd) {
        maxd = dist[u];
        b = u;
      }
      s.push(u);
    }
  }

  return {b, maxd};
}

int dfs_diameter(const vector<vector<int>>& adj, int n, int x) {
  auto b = max_dist(adj, n, x);
  auto c = max_dist(adj, n, b.first);
  return c.second;
}

void dfs1(const vector<vector<int>>& adj, vector<int>& leaf,
          vector<int>& max_len, int v, int p) {
  int max_leaf1 = 0, max_leaf2 = 0;
  for (int u : adj[v]) {
    // skip parent
    if (u == p) {
      continue;
    }

    dfs1(adj, leaf, max_len, u, v);

    int uleaf = leaf[u] + 1;
    if (uleaf > max_leaf1) {
      max_leaf2 = max_leaf1;
      max_leaf1 = uleaf;
    } else if (uleaf > max_leaf2)
      max_leaf2 = uleaf;
  }

  leaf[v] = max_leaf1;
  max_len[v] = max(max_leaf1, max_leaf1 + max_leaf2);
}

int dp_diameter(const vector<vector<int>>& adj, int n, int x) {
  vector<int> leaf(n + 1, 0), max_len(n + 1, 0);
  dfs1(adj, leaf, max_len, x, 0);

  // max among max_len[x] is the diameter
  int diameter = 0;
  for (int v = 1; v <= n; ++v) {
    diameter = max(diameter, max_len[v]);
  }

  return diameter;
}

vector<vector<int>> make_adj(vector<pair<int, int>> edges, int n) {
  vector<vector<int>> adj(n + 1);
  for (auto edge : edges) {
    adj[edge.first].push_back(edge.second);
    adj[edge.second].push_back(edge.first);
  }

  return adj;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n = 7;
  vector<pair<int, int>> edges1 = {
      {1, 2}, //
      {1, 3}, //
      {1, 4}, //
      {2, 5}, //
      {2, 6}, //
      {4, 7}, //
  };

  auto adj1 = make_adj(edges1, n);

  int x = 3;
  // diameter with 2 dfs
  int dfs_diam = dfs_diameter(adj1, n, x);
  cout << "DFS diameter: " << dfs_diam << endl;

  int dp_diam = dp_diameter(adj1, n, x);
  cout << "DP diameter: " << dp_diam << endl;

  int n2 = 6;
  vector<pair<int, int>> edges2 = {
      {1, 2}, //
      {1, 3}, //
      {1, 4}, //
      {2, 5}, //
      {2, 6}, //
  };
  auto adj2 = make_adj(edges2, n2);
  int dp_diam2 = dp_diameter(adj2, n2, 1);
  cout << "DP diameter 2: " << dp_diam2 << endl;
}
