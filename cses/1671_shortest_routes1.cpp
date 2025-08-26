#include <climits>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

typedef long long ll;

const ll INF = LONG_MAX;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, m;
  cin >> n >> m;

  vector<vector<pair<int, ll>>> adjl(n + 1);

  int u, v, w;
  for (int i = 0; i < m; ++i) {
    cin >> u >> v >> w;
    adjl[u].push_back({v, w});
  }

  vector<ll> dist(n + 1, INF);
  vector<bool> vis(n + 1, false);

  priority_queue<pair<ll, int>> q;
  q.push({0, 1});
  dist[1] = 0;

  while (!q.empty()) {
    int u;
    ll uw;
    tie(uw, u) = q.top();
    q.pop();

    if (vis[u]) {
      continue;
    }
    vis[u] = true;

    for (auto val : adjl[u]) {
      int v;
      ll vw;
      tie(v, vw) = val;
      if (v == u || vw == INF || vis[v]) {
        continue;
      }

      if (dist[u] + vw < dist[v]) {
        dist[v] = dist[u] + vw;
        q.push({-dist[v], v});
      }
    }
  }

  for (int v = 1; v <= n; ++v) {
    cout << dist[v] << " ";
  }
}
