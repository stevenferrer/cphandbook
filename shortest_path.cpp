#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <stack>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using Edge = tuple<int, int, int>;

const int INF = 1000000;

Edge make_edge(int a, int b, int w = 0) { return {a, b, w}; }

void bellmanFord(vector<Edge> edges, int vertices, int s = 1) {
  // Refer to below blog post for intuitive explanation:
  // https://medium.com/@shashikanth.gajjelli/bellman-ford-algorithm-for-dummies-99bd9be9b22a

  // assume that distance from s to all nodes is infinity
  vector<int> dist(vertices + 1, INF);
  vector<int> pred(vertices + 1, -1);
  dist[s] = 0;

  // The number of edges are at most V-1
  for (int i = 1; i <= vertices - 1; ++i) {
    for (auto e : edges) {
      int a, b, w;
      tie(a, b, w) = e;

      // Here, we ask if we  can reach b
      // from s via a, that is s -> a -> b.
      // We compare the current distance of b
      // from s, initially infinity, to
      // distance s -> a -> b
      if (dist[a] + w < dist[b]) {
        dist[b] = dist[a] + w;
        pred[b] = a;
      }
    }
  }

  for (int i = 1; i <= vertices; ++i) {
    // trace shortest-path from s
    stack<int> sp;
    int c = i;
    while (pred[c] > 0) {
      sp.push(c);
      c = pred[c];
    }
    sp.push(s);

    // print shortest-path from s
    while (!sp.empty()) {
      cout << sp.top();
      sp.pop();
      if (!sp.empty()) {
        cout << " -> ";
      }
    }

    printf(" (%d)\n", dist[i]);
  }
}

void dijkstra(vector<vector<pair<int, int>>> adj, int n, int origin) {
  vector<int> dist(n + 1, INF);
  vector<bool> done(n + 1, false);

  // -distance, node
  priority_queue<pair<int, int>> q;

  dist[origin] = 0;
  q.push({0, origin});

  while (!q.empty()) {
    int a = q.top().second;
    q.pop();

    if (done[a]) {
      continue;
    }
    done[a] = true;

    for (auto u : adj[a]) {
      int b, w;
      tie(b, w) = u;

      if (dist[a] + w < dist[b]) {
        dist[b] = dist[a] + w;

        q.push({-dist[b], b});
      }
    }
  }

  for (int i = 1; i <= n; ++i) {
    cout << dist[i] << " ";
  }
  cout << endl;
}

const vector<pair<int, int>> directions = {
    {1, 0},  // up
    {0, 1},  // right
    {1, 0},  // down
    {0, -1}, // left
};

void dijkstra2D(vector<vector<int>> mat, pair<int, int> s = {0, 0}) {
  int rows = mat.size(), cols = mat[0].size();
  vector<vector<int>> dist(rows + 1, vector<int>(cols + 1, INF));
  vector<vector<bool>> done(rows + 1, vector<bool>(cols + 1, false));

  priority_queue<tuple<int, int, int>> q;

  int srow = s.first, scol = s.second;
  dist[srow][scol] = 0;

  q.push({mat[srow][scol], srow, scol});

  while (!q.empty()) {
    int _w, r, c;
    tie(_w, r, c) = q.top();
    q.pop();

    if (done[r][c]) {
      continue;
    }
    done[r][c] = true;

    for (auto dir : directions) {
      int nr = r + dir.first;
      int nc = c + dir.second;

      // out-of-bounds check
      if (nr < 0 || nc < 0 || nr >= rows || nc >= cols) {
        continue;
      }

      int w = mat[nr][nc];

      if (dist[r][c] + w < dist[nr][nc]) {
        dist[nr][nc] = dist[r][c] + w;
        q.push({-dist[nr][nc], nr, nc});
      }
    }
  }

  // print shortest-path to any cell
  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      if (dist[r][c] == INF) {
        cout << "∞";
      } else {
        cout << dist[r][c];
      }
      cout << " ";
    }
    cout << endl;
  }
}

void floydWarshall(vector<vector<int>> adjm, int vertices) {
  vector<vector<int>> dist(vertices, vector<int>(vertices, INF));

  for (int r = 0; r < vertices; ++r) {
    for (int c = 0; c < vertices; ++c) {
      if (r == c) {
        dist[r][c] = 0;
      } else if (adjm[r][c]) {
        dist[r][c] = adjm[r][c];
      } else {
        dist[r][c] = INF;
      }
    }
  }

  for (int k = 0; k < vertices; ++k) {
    for (int r = 0; r < vertices; ++r) {
      for (int c = 0; c < vertices; ++c) {
        dist[r][c] = min(dist[r][c], dist[r][k] + dist[k][c]);
      }
    }
  }

  for (int r = 0; r < vertices; ++r) {
    for (int c = 0; c < vertices; ++c) {
      cout << dist[r][c] << " ";
    }
    cout << endl;
  }
}

int main() {
  vector<Edge> edges = {
      {1, 2, 2}, //
      {1, 3, 7}, //
      {1, 3, 1}, //

      {2, 5, 5}, //
      {2, 4, 3}, //

      {3, 4, 3}, //
      {4, 5, 2}, //
  };

  cout << "Bellman-Ford: " << endl;
  bellmanFord(edges, 5, 1);

  vector<vector<pair<int, int>>> adj1(5 + 1);
  adj1[1].push_back({2, 5});
  adj1[1].push_back({4, 9});
  adj1[1].push_back({5, 1});
  adj1[2].push_back({3, 2});
  adj1[3].push_back({4, 6});
  adj1[4].push_back({5, 2});

  cout << "Dijkstra: " << endl;
  dijkstra(adj1, 5, 1);

  vector<vector<int>> mat = {
      {1, 3, INF, 1, 1}, //
      {1, 1, 5, 1, 1},   //
      {1, 1, 1, 1, 1},   //
      {1, 1, 1, 1, 1},   //
      {1, 1, 1, 1, 1},   //
  };

  cout << "Dijkstra 2D: " << endl;
  dijkstra2D(mat, {0, 0});

  vector<vector<int>> adjm = {
      {0, 5, INF, 9, 1},   //
      {5, 0, 2, INF, INF}, //
      {INF, 2, 0, 7, INF}, //
      {9, INF, 7, 0, 2},   //
      {1, INF, INF, 2, 0}, //
  };

  cout << "Floyd-Warshall: " << endl;
  floydWarshall(adjm, 5);
}
