#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

template <class T> class FenwickTree {
public:
  FenwickTree(size_t n) {
    t.assign(n + 1, 0);
    a.assign(n + 1, 0);
  }

  void set(size_t k, T u) {
    add(k, u - a[k]);
    a[k] = u;
  }

  void add(size_t k, T delta) {
    // start at k and propagate values upward
    while (k < t.size()) {
      t[k] += delta;
      k += (k & -k);
    }
  }

  T sum(size_t k) {
    // sum of values from k upwards
    T s = 0;
    while (k >= 1) {
      s += t[k];
      k -= (k & -k);
    }

    return s;
  }

  T sum(size_t l, size_t r) {
    auto lsum = sum(l - 1);
    auto rsum = sum(r);
    return rsum - lsum;
  }

  T at(size_t k) { return t[k]; }

private:
  vector<T> t, a;
};

class Tour {
public:
  vector<size_t> start, end;

  Tour(const vector<vector<int>>& adj, size_t n) : adj{adj} {
    start.assign(n + 1, 0);
    end.assign(n + 1, 0);

    index = 0;
    dfs(1, 0);
  }

private:
  vector<vector<int>> adj;
  size_t index;

  void dfs(int v, int p) {
    start[v] = ++index;

    for (auto u : adj[v]) {
      if (u == p) {
        continue;
      }
      dfs(u, v);
    }

    end[v] = index;
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  size_t n, q;
  cin >> n >> q;

  vector<ll> vals(n);
  for (size_t i = 0; i < n; ++i) {
    cin >> vals[i];
  }

  vector<vector<int>> adj(n + 1);

  int a, b;
  for (size_t i = 0; i < n - 1; ++i) {
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  Tour t(adj, n);

  FenwickTree<ll> ft(n);
  for (size_t i = 1; i <= n; ++i) {
    ft.set(t.start[i], vals[i - 1]);
  }

  while (q--) {
    int qt, v;
    ll x;
    cin >> qt >> v;

    if (qt == 1) {
      cin >> x;
      ft.set(t.start[v], x);
      continue;
    }

    cout << ft.sum(t.start[v], t.end[v]) << "\n";
  }
}
