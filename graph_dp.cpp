#include <iostream>
#include <queue>
#include <stack>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

const int INF = 1000000;

int pathCount(vector<vector<int>> adjl, int n, int start, int end) {
  vector<bool> visited(n + 1, false);
  vector<int> paths(n + 1, 0);
  paths[start] = 1;

  stack<int> s;
  s.push(start);

  while (!s.empty()) {
    int v = s.top();
    s.pop();

    if (visited[v]) {
      continue;
    }
    visited[v] = true;

    for (int u : adjl[v]) {
      paths[u] += paths[v];
      s.push(u);
    }
  }

  return paths[end];
}

void shortestPathDAG(vector<vector<pair<int, int>>> adjl, int n, int origin) {
  // find shortest paths from origin to any node
  // build a DAG based on the shortest-path

  vector<bool> done(n + 1, false);
  vector<int> dist(n + 1, INF);
  vector<int> pred(n + 1, -1);

  priority_queue<pair<int, int>> q;
  q.push({0, origin});
  dist[origin] = 0;

  while (!q.empty()) {
    int a = q.top().second;
    q.pop();

    if (done[a]) {
      continue;
    }
    done[a] = true;

    for (auto u : adjl[a]) {
      int b, w;
      tie(b, w) = u;

      if (dist[a] + w < dist[b]) {
        dist[b] = dist[a] + w;
        pred[b] = a;
        q.push({-dist[b], b});
      }
    }
  }

  // paths in reverse
  for (int v = 1; v <= n; ++v) {
    // if we want to know the cost from b <- pred[b]
    // we can look at the cost from the adjacency list or;
    // build an adjacency matrix so the look-up faster
    int b = v;
    while (b != -1) {
      cout << b;
      b = pred[b];
      if (b != -1) {
        cout << "<-";
      }
    }

    cout << endl;
  }
}

vector<vector<pair<int, int>>>
buildWeightedAdjl(vector<tuple<int, int, int>> edges, int n,
                  bool birectional = true) {
  vector<vector<pair<int, int>>> adjl(n + 1);

  for (auto edge : edges) {
    int a, b, w;
    tie(a, b, w) = edge;
    adjl[a].push_back({b, w});
    if (birectional) {
      adjl[b].push_back({a, w});
    }
  }

  return adjl;
}

// This function builds a DAG version of the coin problem
vector<vector<int>> coinGraph(vector<int>& coins, int n) {
  // vector<pair<int, int>> edges;
  vector<vector<int>> adjl(n + 1);

  for (int x = 1; x <= n; ++x) {
    for (auto c : coins) {
      if (x - c >= 0) {
        adjl[x - c].push_back(x);
      }
    }
  }

  return adjl;
}

int coinDistance(vector<vector<int>>& adjl, int n) {
  vector<int> dist(n + 1, INF);
  vector<bool> vis(n + 1, false);

  queue<int> q;
  q.push(0);
  dist[0] = 0;

  while (!q.empty()) {
    auto v = q.front();
    q.pop();

    if (vis[v]) {
      continue;
    }
    vis[v] = true;

    for (auto u : adjl[v]) {
      if (vis[u]) {
        continue;
      }

      if (dist[v] + 1 < dist[u]) {
        dist[u] = dist[v] + 1;
        q.push(u);
      }
    }
  }

  return dist[n];
}

int main() {
  int n1 = 6;
  vector<vector<int>> adjl1(n1 + 1);
  adjl1[1].push_back(2);
  adjl1[1].push_back(4);
  adjl1[2].push_back(3);
  adjl1[2].push_back(6);
  adjl1[3].push_back(6);
  adjl1[4].push_back(5);
  adjl1[5].push_back(2);

  cout << "Path count: " << pathCount(adjl1, n1, 1, 6) << endl;

  vector<tuple<int, int, int>> edges1 = {
      {1, 2, 3}, //
      {1, 3, 5}, //
      {2, 3, 2}, //
      {2, 4, 4}, //
      {2, 5, 8}, //
      {3, 4, 2}, //
      {4, 5, 1}, //
  };

  auto adjl2 = buildWeightedAdjl(edges1, 5);
  cout << "Shortest-path DAG: \n";
  shortestPathDAG(adjl2, 5, 1);

  cout << "Coin problem as graph: \n";
  vector<int> coins = {1, 3, 4};
  int n = 6;
  auto adjl3 = coinGraph(coins, n);
  // print coin graph edges
  for (int v = 0; v <= n; ++v) {
    for (auto u : adjl3[v]) {
      cout << v << "->" << u << "\n";
    }
  }

  // we reused the coin graph from above, but both functions below
  // can build their own graph from the given coins
  cout << "Mininum coins for sum of 6: " << coinDistance(adjl3, n) << endl;
  cout << "Coin solutions for sum of 3: " << pathCount(adjl3, n, 0, 3);
}
