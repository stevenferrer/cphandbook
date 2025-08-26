#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

void printNode(int node) { cout << node << " "; }
void dummy(int _) {};

void dfsi(vector<vector<int>>& adjl, int n, int a,
          std::function<void(int)> fn) {
  vector<bool> visited(n + 1, false);
  stack<int> s;

  s.push(a);

  while (!s.empty()) {
    int v = s.top();
    s.pop();

    // skip visited
    if (visited[v]) {
      continue;
    }
    // mark as visited
    visited[v] = true;

    // process
    fn(v);

    // we use reverse iterator to imitate recursive order
    for (auto b = adjl[v].rbegin(); b != adjl[v].rend(); ++b) {

      // cycle detected
      if (visited[*b]) {
        continue;
      }

      // visit neighbors later
      s.push(*b);
    }
  }
}

void dfsr(vector<vector<int>>& adjl, vector<bool>& visited, int a,
          std::function<void(int)> fn) {
  visited[a] = true;

  // process node
  fn(a);

  for (auto b : adjl[a]) {
    if (visited[b]) {
      continue;
    }

    // visit the neighbor
    dfsr(adjl, visited, b, fn);
  }
}

void bfs(vector<vector<int>>& adjl, int n, int start,
         std::function<void(int)> fn) {
  vector<bool> visited(n + 1, false);
  // set distance of
  vector<int> dist(n + 1, 999999);

  queue<int> q;
  q.push(start);

  // distance to starting node is 0
  dist[start] = 0;

  while (!q.empty()) {
    int v = q.front();
    q.pop();

    if (visited[v]) {
      continue;
    }
    visited[v] = true;

    // process node
    fn(v);

    for (auto u : adjl[v]) {
      if (visited[u]) {
        continue;
      }

      if (dist[v] + 1 < dist[u]) {
        dist[u] = dist[v] + 1;
      }

      q.push(u);
    }
  }
}

const vector<pair<int, int>> directions = {
    {1, 0},  // up
    {0, 1},  // right
    {1, 0},  // down
    {0, -1}, // left
};

void dfs2D(vector<vector<int>>& adjm, pair<int, int> a,
           std::function<void(int)> fn) {
  int rows = adjm.size();
  int cols = adjm[0].size();
  vector<vector<bool>> visited(rows, vector<bool>(cols, false));

  stack<pair<int, int>> s;
  s.push(a);

  while (!s.empty()) {
    int r, c;
    tie(r, c) = s.top();
    s.pop();

    if (visited[r][c]) {
      continue;
    }

    visited[r][c] = true;

    // process
    fn(adjm[r][c]);

    for (auto dir : directions) {
      int nr = r + dir.first;
      int nc = c + dir.second;

      // out-of-bounds check
      if (nr < 0 || nc < 0 || nr >= rows || nc >= cols) {
        continue;
      }

      s.push({nr, nc});
    }
  }
}

void bfs2D(vector<vector<int>>& adjm, pair<int, int> a,
           std::function<void(int)> fn) {
  int rows = adjm.size();
  int cols = adjm[0].size();
  vector<vector<bool>> visited(rows, vector<bool>(cols, false));
  vector<vector<int>> distance(rows, vector<int>(cols, 0));

  queue<pair<int, int>> q;
  q.push(a);

  // TODO: check that we don't double visit

  while (!q.empty()) {
    int r, c;
    tie(r, c) = q.front();
    q.pop();

    if (visited[r][c]) {
      continue;
    }

    visited[r][c] = true;

    fn(adjm[r][c]);

    for (auto dir : directions) {
      int nr = r + dir.first;
      int nc = c + dir.second;

      // out-of-bounds check
      if (nr < 0 || nc < 0 || nr >= rows || nc >= cols) {
        continue;
      }

      distance[nr][nc] = distance[r][c] + 1;
      q.push({nr, nc});
    }
  }

  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      cout << distance[r][c] << " ";
    }
    cout << endl;
  }
}

bool isConnected(vector<vector<int>>& adjl, int n, int a) {
  // if the graph is connected, all the nodes
  // should be marked as visited by the end
  // of the search
  vector<bool> visited(n + 1, false);

  stack<int> s;
  s.push(a);

  while (!s.empty()) {
    int v = s.top();
    s.pop();

    // we already have a check
    // inside the for-loop, so
    // this is probably unnecessary
    if (visited[v]) {
      continue;
    }

    visited[v] = true;

    for (auto b : adjl[v]) {
      // cycle detected
      if (visited[b]) {
        continue;
      }

      s.push(b);
    }
  }

  // all nodes must be visited
  return all_of(visited.begin(), visited.end(), [](bool v) { return v; });
}

bool detectCycle(vector<vector<int>>& adjl, int n, int a) {
  // if the graph has cycle, the neighbor of the current
  // node will be marked as visited
  vector<bool> visited(n + 1, false);

  stack<pair<int, int>> s;
  s.push({a, -1});

  while (!s.empty()) {
    int v, prev;
    tie(v, prev) = s.top();
    s.pop();

    // unnecessary check, we include
    // just in-case you didn't add
    // a check inside the for-loop?
    if (visited[v]) {
      continue;
    }

    visited[v] = true;

    for (auto b : adjl[v]) {
      // TODO: double check
      // cycle detected if b is
      // visited and it's not a
      // predecessor node
      if (visited[b]) {
        return true;
      }

      s.push({b, a});
    }
  }

  return false;
}

bool isBipartite(vector<vector<int>>& adjl, int n, int a) {
  // if the graph has cycle, the neighbor of the current
  // node will be marked as visited
  vector<bool> visited(n + 1, false);
  vector<int> colors(n + 1, -1);

  stack<pair<int, int>> s;
  // colors are 0 and 1
  s.push({a, 0});

  while (!s.empty()) {
    int v, c;
    tie(v, c) = s.top();
    s.pop();

    // unnecessary check, we include
    // just in-case you didn't add
    // a check inside the for-loop?
    if (visited[v]) {
      continue;
    }

    visited[v] = true;
    colors[v] = c;

    for (auto b : adjl[v]) {
      // neighbor has same color!
      // also this is cycle
      if (colors[b] == c) {
        return false;
      }

      // flip the color of neighbor
      s.push({b, !c});
    }
  }

  return true;
}

int main() {
  const int n = 5;
  vector<vector<int>> graph1(n + 1);
  graph1[0].push_back(1);
  graph1[1].push_back(2);
  graph1[1].push_back(5);
  graph1[2].push_back(3);
  graph1[2].push_back(4);

  cout << "DFS:\n";
  vector<bool> visited(n, false);
  dfsr(graph1, visited, 0, printNode);
  cout << endl;

  cout << "DFS(iterative):\n";
  dfsi(graph1, n, 0, printNode);
  cout << endl;

  cout << "BFS:\n";
  bfs(graph1, n, 0, printNode);
  cout << endl;

  // 2D grid
  vector<vector<int>> graph2d({
      {1, 2, 3, 4},     //
      {5, 6, 7, 8},     //
      {9, 10, 11, 12},  //
      {13, 14, 15, 16}, //
  });

  cout << "DFS 2D:\n";
  dfs2D(graph2d, {0, 0}, printNode);
  cout << endl;

  cout << "BFS 2D:\n";
  bfs2D(graph2d, {0, 0}, dummy);
  cout << endl;

  vector<vector<int>> graph2(n + 1);

  // 0 is not connected to any nodes
  graph2[1].push_back(2);
  graph2[1].push_back(5);
  graph2[1].push_back(4); // 1->4
  graph2[2].push_back(3);
  graph2[2].push_back(4);
  graph2[4].push_back(1); // 4->1

  cout << "Connectivity check: " << endl;
  cout << "graph1 is connected: " << isConnected(graph1, n, 0) << endl;
  cout << "graph2 is connected: " << isConnected(graph2, n, 0) << endl;

  cout << "Detect cycle: " << endl;
  cout << "graph1 has cycle: " << detectCycle(graph1, n, 1) << endl;
  cout << "graph2 has cycle: " << detectCycle(graph2, n, 1) << endl;

  // non-bipartite graph
  vector<vector<int>> graph3(n + 1);
  graph3[1].push_back(2);
  graph3[1].push_back(4);
  graph3[2].push_back(3);
  graph3[3].push_back(5);
  graph3[5].push_back(2);

  // bipartite graph
  vector<vector<int>> graph4(n + 1);
  graph4[1].push_back(2);
  graph4[1].push_back(4);
  graph4[2].push_back(3);
  graph4[3].push_back(5);

  cout << "Bipartite check: " << endl;
  cout << "graph3 is bipartite: " << isBipartite(graph3, n, 1) << endl;
  cout << "graph4 is bipartite: " << isBipartite(graph4, n, 1) << endl;
}
