#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

vector<vector<int>> make_adj(vector<pair<int, int>> edges, int n) {
  vector<vector<int>> adj(n + 1);
  for (auto e : edges) {
    adj[e.first].push_back(e.second);
    adj[e.second].push_back(e.first);
  }

  return adj;
}

void dfs1(const vector<vector<int>>& adj, vector<int>& max_len1,
          vector<int>& max_len2, int v, int p) {
  int max_leaf1 = 0, max_leaf2 = 0;
  for (int u : adj[v]) {
    // skip parent
    if (u == p) {
      continue;
    }

    dfs1(adj, max_len1, max_len2, u, v);

    int uleaf = max_len1[u] + 1;
    if (uleaf > max_leaf1) {
      max_leaf2 = max_leaf1;
      max_leaf1 = uleaf;
    } else if (uleaf > max_leaf2)
      max_leaf2 = uleaf;
  }

  max_len1[v] = max_leaf1;
  max_len2[v] = max_leaf2;
}

void dfs2(const vector<vector<int>>& adj, vector<int>& max_len1,
          vector<int>& max_len2, vector<int>& max_lenp, int v, int p) {

  for (auto u : adj[v]) {
    if (u == p) {
      continue;
    }

    int best = (max_len1[v] == 1 + max_len1[u] ? max_len2[v] : max_len1[v]);
    max_lenp[u] = 1 + max(max_lenp[v], best);
    dfs2(adj, max_len1, max_len2, max_lenp, u, v);
  }
}

vector<int> longest_paths(const vector<vector<int>>& adj, int n, int x) {
  vector<int> max_len1(n + 1, 0), max_len2(n + 1, 0), max_lenp(n + 1, 0);

  dfs1(adj, max_len1, max_len2, x, 0);
  max_lenp[x] = 0;
  dfs2(adj, max_len1, max_len2, max_lenp, x, 0);

  vector<int> max_lens(n + 1, 0);
  for (int v = 1; v <= n; ++v) {
    max_lens[v] = max(max_len1[v], max_lenp[v]);
  }

  return max_lens;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n = 6;
  vector<pair<int, int>> edges = {
      {1, 2}, //
      {1, 3}, //
      {1, 4}, //
      {2, 5}, //
      {2, 6}, //
  };
  auto adj = make_adj(edges, n);

  auto max_lens = longest_paths(adj, n, 1);
  for (int v = 1; v <= n; ++v) {
    cout << max_lens[v] << endl;
  }
}
