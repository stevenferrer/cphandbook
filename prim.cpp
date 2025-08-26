#include <cstdio>
#include <iostream>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

const int INF = 1e9;

vector<vector<pair<int, int>>> prims(vector<vector<pair<int, int>>>& adjl,
                                     int n, int start = 1) {
  vector<bool> selected(n + 1, false);
  vector<int> min_weight(n + 1, INF);
  vector<int> min_edge(n + 1, -1);

  priority_queue<pair<int, int>> q;

  // sort by -weight and -label
  q.push({0, -start});
  min_weight[start] = 0;

  while (!q.empty()) {
    int u, uw;
    tie(uw, u) = q.top();
    q.pop();

    uw = -uw, u = -u;
    if (selected[u]) {
      continue;
    }
    selected[u] = true;

    for (auto neighbor : adjl[u]) {
      int v, vw;
      tie(v, vw) = neighbor;
      if (selected[v]) {
        continue;
      }

      // update minimum weight of v
      if (vw < min_weight[v]) {
        min_weight[v] = vw;
        min_edge[v] = u;
        q.emplace(-vw, -v);
      }
    }
  }

  vector<vector<pair<int, int>>> mst(n + 1, vector<pair<int, int>>());
  for (int u = 1; u <= n; ++u) {
    if (min_edge[u] == -1) {
      continue;
    }

    int e = min_edge[u];
    mst[e].push_back({u, min_weight[u]});
  }

  return mst;
}

int main() {
  int n = 6;

  vector<tuple<int, int, int>> edges = {
      {1, 5, 5}, //
      {1, 2, 3}, //
      {2, 5, 6}, //
      {2, 3, 5}, //
      {3, 4, 9}, //
      {3, 6, 3}, //
      {4, 6, 7}, //
      {5, 6, 2}, //
  };

  vector<vector<pair<int, int>>> adjl(n + 1);
  for (auto edge : edges) {
    int u, v, w;
    tie(u, v, w) = edge;
    adjl[u].push_back({v, w});
    adjl[v].push_back({u, w});
  }

  cout << "Prim's algorithm: \n";
  auto mst = prims(adjl, n);

  int total_cost = 0;
  for (int u = 1; u <= n; ++u) {
    for (auto neighbor : mst[u]) {
      int v, w;
      tie(v, w) = neighbor;
      printf("%d->%d\n", u, v);
      total_cost += w;
    }
  }
  cout << "Total cost: " << total_cost << endl;
}
