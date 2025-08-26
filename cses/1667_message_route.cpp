#include <iostream>
#include <iterator>
#include <queue>
#include <vector>

using namespace std;

const int INF = 1000000;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, m;
  cin >> n >> m;

  vector<vector<int>> adjl(n + 1);

  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    adjl[a].push_back(b);
    adjl[b].push_back(a);
  }

  vector<int> dist(n + 1, INF);
  vector<int> pred(n + 1, 0);
  vector<int> done(n + 1, false);

  priority_queue<pair<int, int>> q;
  dist[1] = 0;
  q.push({0, 1});

  while (!q.empty()) {
    int a = q.top().second;
    q.pop();

    if (done[a]) {
      continue;
    }
    done[a] = true;

    for (auto b : adjl[a]) {
      if (done[b]) {
        continue;
      }

      if (dist[a] + 1 < dist[b]) {
        dist[b] = dist[a] + 1;
        pred[b] = a;
        q.push({-dist[b], b});
      }
    }
  }

  if (dist[n] == INF) {
    cout << "IMPOSSIBLE";
    return 0;
  }

  vector<int> path;
  int v = n;
  while (v) {
    path.push_back(v);
    v = pred[v];
  }

  cout << path.size() << "\n";
  for (auto it = path.rbegin(); it != path.rend(); ++it) {
    cout << *it << " ";
  }
}
